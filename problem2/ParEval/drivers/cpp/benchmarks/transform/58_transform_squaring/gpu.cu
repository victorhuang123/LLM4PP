// Driver for 55_transform_squaring
// /* Replace every element of x with the square of its value.
//    Use CUDA to compute in parallel. The kernel is launched with at least as many threads as values in x.
//    Example:
// 
//    input: [5, 1, 2, -4, 8]
//    output: [25, 1, 4, 16, 64]
// */
// __global__ void squareEach(int *x, size_t N) {

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "utilities.hpp"
#include "baseline.hpp"
#include "generated-code.cuh"   // code generated by LLM


#if defined(USE_CUDA)
#include <thrust/device_vector.h>
#include <thrust/copy.h>
#include <thrust/sort.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/iterator/permutation_iterator.h>
#endif


struct Context {
    int *x;
    size_t N;
    std::vector<int> cpuX;
    dim3 blockSize, gridSize;
};

void reset(Context *ctx) {
    fillRand(ctx->cpuX, -50, 50);
    COPY_H2D(ctx->x, ctx->cpuX.data(), ctx->N * sizeof(int));
}

Context *init() {
    Context *ctx = new Context();

    ctx->N = DRIVER_PROBLEM_SIZE;
    ctx->blockSize = dim3(1024);
    ctx->gridSize = dim3((ctx->N + ctx->blockSize.x - 1) / ctx->blockSize.x); // at least enough threads

    ALLOC(ctx->x, ctx->N * sizeof(int));
    ctx->cpuX.resize(ctx->N);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    squareEach<<<ctx->gridSize,ctx->blockSize>>>(ctx->x, ctx->N);
}

void NO_OPTIMIZE best(Context *ctx) {
    correctSquareEach(ctx->cpuX);
}

bool validate(Context *ctx) {

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int i = 0; i < numTries; i += 1) {
        std::vector<int> input(1024);
        fillRand(input, -50, 50);

        // compute correct result
        std::vector<int> correctResult = input;
        correctSquareEach(correctResult);

        // compute test result
        int *testResultDevice;
        ALLOC(testResultDevice, input.size() * sizeof(int));
        COPY_H2D(testResultDevice, input.data(), input.size() * sizeof(int));
        dim3 blockSize = dim3(1024);
        dim3 gridSize = dim3((input.size() + blockSize.x - 1) / blockSize.x); // at least enough threads
        squareEach<<<gridSize,blockSize>>>(testResultDevice, input.size());
        SYNC();

        std::vector<int> testResult(input.size());
        COPY_D2H(testResult.data(), testResultDevice, testResult.size() * sizeof(int));
        
        if (!std::equal(correctResult.begin(), correctResult.end(), testResult.begin())) {
            return false;
        }
    }

    return true;
}

void destroy(Context *ctx) {
    FREE(ctx->x);
    delete ctx;
}


