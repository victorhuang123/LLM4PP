// Driver for 26_reduce_product_of_inverses for CUDA and HIP
// /* Compute the product of the vector x with every odd indexed element inverted.
//    i.e. x_0 * 1/x_1 * x_2 * 1/x_3 * x_4 ...
//    Store the result in product.
//    Use CUDA to compute product in parallel. The kernel is launched with at least as many threads as values in x.
//    Example:
//
//    input: [4, 2, 10, 4, 5]
//    output: 25
// */
// __global__ void productWithInverses(const double *x, size_t N, double *product) {

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "utilities.hpp"
#include "baseline.hpp"
#include "generated-code.cuh"   // code generated by LLM

struct Context {
    double *d_x, *d_output;
    std::vector<double> h_x;
    size_t N;
    dim3 blockSize, gridSize;
};

void reset(Context *ctx) {
    fillRand(ctx->h_x, 0.0, 100.0);
    COPY_H2D(ctx->d_x, ctx->h_x.data(), ctx->N * sizeof(double));

    double tmp = 1.0;
    COPY_H2D(ctx->d_output, &tmp, sizeof(double));
}

Context *init() {
    Context *ctx = new Context();

    ctx->N = DRIVER_PROBLEM_SIZE;
    ctx->blockSize = dim3(1024);
    ctx->gridSize = dim3((ctx->N + ctx->blockSize.x - 1) / ctx->blockSize.x); // at least enough threads

    ctx->h_x.resize(ctx->N);
    ALLOC(ctx->d_x, ctx->N * sizeof(double));
    ALLOC(ctx->d_output, sizeof(double));

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    productWithInverses<<<ctx->gridSize, ctx->blockSize>>>(ctx->d_x, ctx->N, ctx->d_output);
}

void NO_OPTIMIZE best(Context *ctx) {
    double output = correctProductWithInverses(ctx->h_x);
    (void)output;
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;
    dim3 blockSize = dim3(1024);
    dim3 gridSize = dim3((TEST_SIZE + blockSize.x - 1) / blockSize.x); // at least enough threads

    std::vector<double> h_x(TEST_SIZE);
    double correct, test;

    double *d_x, *d_test;
    ALLOC(d_x, TEST_SIZE * sizeof(double));
    ALLOC(d_test, sizeof(double));

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        fillRand(h_x, 0.0, 100.0);
        COPY_H2D(d_x, h_x.data(), TEST_SIZE * sizeof(double));

        double tmp = 1.0;
        COPY_H2D(d_test, &tmp, sizeof(double));

        // compute correct result
        correct = correctProductWithInverses(h_x);

        // compute test result
        productWithInverses<<<gridSize, blockSize>>>(d_x, TEST_SIZE, d_test);
        SYNC();

        // copy back
        COPY_D2H(&test, d_test, sizeof(double));

        if (std::abs(correct - test) > 1e-4) {
            FREE(d_x);
            FREE(d_test);
            return false;
        }
    }

    FREE(d_x);
    FREE(d_test);
    return true;
}

void destroy(Context *ctx) {
    FREE(ctx->d_x);
    FREE(ctx->d_output);
    delete ctx;
}
