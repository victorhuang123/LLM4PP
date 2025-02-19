// Driver for 48_sparse_la_sparse_axpy for Serial, OpenMP, MPI, and MPI+OpenMP
// struct Element {
// 	size_t index;
//   double value;
// };
// 
// /* Compute z = alpha*x+y where x and y are sparse vectors. Store the result in z.
//    Example:
//    
//    input: x=[{5, 12}, {8, 3}, {12, -1}], y=[{3, 1}, {5, -2}, {7, 1}, {8, -3}], alpha=1
//    output: z=[{3, 1}, {5, 10}, {7, 1}, {12, -1}]
// */
// void sparseAxpy(double alpha, std::vector<Element> const& x, std::vector<Element> const& y, std::vector<double> &z) {

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>
#include <map>
#include <unordered_map>

#include "utilities.hpp"
#include "generated-code.hpp"   // code generated by LLM
#include "baseline.hpp"

struct Context {
    std::vector<Element> x, y;
    std::vector<size_t> xIndices, yIndices;
    std::vector<double> xValues, yValues, z;
    double alpha;
    size_t N;
};

void reset(Context *ctx) {
    ctx->alpha = (rand() / (double) RAND_MAX) * 2.0 - 1.0;
    fillRand(ctx->xIndices, 0UL, ctx->N);
    fillRand(ctx->yIndices, 0UL, ctx->N);
    fillRand(ctx->xValues, -1.0, 1.0);
    fillRand(ctx->yValues, -1.0, 1.0);

    BCAST_PTR(&ctx->alpha, 1, DOUBLE);
    BCAST(ctx->xIndices, UNSIGNED_LONG);
    BCAST(ctx->yIndices, UNSIGNED_LONG);
    BCAST(ctx->xValues, DOUBLE);
    BCAST(ctx->yValues, DOUBLE);

    for (int i = 0; i < ctx->xIndices.size(); i += 1) {
        ctx->x[i] = {ctx->xIndices[i], ctx->xValues[i]};
        ctx->y[i] = {ctx->yIndices[i], ctx->yValues[i]};
    }
    std::sort(ctx->x.begin(), ctx->x.end(), [](Element const& a, Element const& b) { return a.index < b.index; });
    std::sort(ctx->y.begin(), ctx->y.end(), [](Element const& a, Element const& b) { return a.index < b.index; });

    std::fill(ctx->z.begin(), ctx->z.end(), 0.0);
}

Context *init() {
    Context *ctx = new Context();

    ctx->N = DRIVER_PROBLEM_SIZE;
    const size_t nVals = ctx->N * SPARSE_LA_SPARSITY;
    ctx->x.resize(nVals);
    ctx->y.resize(nVals);
    ctx->xIndices.resize(nVals);
    ctx->yIndices.resize(nVals);
    ctx->xValues.resize(nVals);
    ctx->yValues.resize(nVals);

    ctx->z.resize(ctx->N);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    sparseAxpy(ctx->alpha, ctx->x, ctx->y, ctx->z);
}

void NO_OPTIMIZE best(Context *ctx) {
    correctSparseAxpy(ctx->alpha, ctx->x, ctx->y, ctx->z);
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;
    const size_t nVals = TEST_SIZE * SPARSE_LA_SPARSITY;

    std::vector<Element> x(nVals), y(nVals);
    std::vector<double> correct(TEST_SIZE), test(TEST_SIZE);
    std::vector<size_t> xIndices(nVals), yIndices(nVals);
    std::vector<double> xValues(nVals), yValues(nVals);

    int rank;
    GET_RANK(rank);

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        double alpha = (rand() / (double) RAND_MAX) * 2.0 - 1.0;
        fillRand(xIndices, 0UL, TEST_SIZE);
        fillRand(yIndices, 0UL, TEST_SIZE);
        fillRand(xValues, -1.0, 1.0);
        fillRand(yValues, -1.0, 1.0);

        BCAST_PTR(&alpha, 1, DOUBLE);
        BCAST(xIndices, UNSIGNED_LONG);
        BCAST(yIndices, UNSIGNED_LONG);
        BCAST(xValues, DOUBLE);
        BCAST(yValues, DOUBLE);

        for (int i = 0; i < xIndices.size(); i += 1) {
            x[i] = {xIndices[i], xValues[i]};
            y[i] = {yIndices[i], yValues[i]};
        }
        std::sort(x.begin(), x.end(), [](Element const& a, Element const& b) { return a.index < b.index; });
        std::sort(y.begin(), y.end(), [](Element const& a, Element const& b) { return a.index < b.index; });

        std::fill(correct.begin(), correct.end(), 0.0);
        std::fill(test.begin(), test.end(), 0.0);

        // compute correct result
        correctSparseAxpy(alpha, x, y, correct);

        // compute test result
        // test.clear();
        sparseAxpy(alpha, x, y, test);
        SYNC();
        
        bool isCorrect = true;
        if (IS_ROOT(rank) && !fequal(correct, test, 1e-4)) {
            isCorrect = false;
        }
        BCAST_PTR(&isCorrect, 1, CXX_BOOL);
        if (!isCorrect) {
            return false;
        }
    }

    return true;
}

void destroy(Context *ctx) {
    delete ctx;
}
