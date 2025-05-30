// Driver for 43_sort_sort_an_array_of_structs_by_key for CUDA and HIP
// struct Result {
//    int startTime, duration;
//    float value;
// };
// 
// /* Sort vector of Result structs by start time in ascending order.
//    Use CUDA to sort in parallel. The kernel is launched with at least as many threads as there are elements.
//    Example:
//    
//    input: [{startTime=8, duration=4, value=-1.22}, {startTime=2, duration=10, value=1.0}, {startTime=10, duration=3, value=0.0}]
//    output: [{startTime=2, duration=10, value=1.0}, {startTime=8, duration=4, value=-1.22}, {startTime=10, duration=3, value=0.0}]
// */
// __global__ void sortByStartTime(Result *results, size_t N) {

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "utilities.hpp"
#include "generated-code.cuh"   // code generated by LLM
#include "baseline.hpp"

struct Context {
    Result *d_results;
    std::vector<Result> h_results;
    size_t N;
    dim3 blockSize, gridSize;
};

void reset(Context *ctx) {
    for (int i = 0; i < ctx->N; i += 1) {
        ctx->h_results[i].startTime = rand() % 100;
        ctx->h_results[i].duration = rand() % 10 + 1;
        ctx->h_results[i].value = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
    }

    COPY_H2D(ctx->d_results, ctx->h_results.data(), ctx->N * sizeof(Result));
}

Context *init() {
    Context *ctx = new Context();

    ctx->N = DRIVER_PROBLEM_SIZE;
    ctx->blockSize = dim3(1024);
    ctx->gridSize = dim3((ctx->N + ctx->blockSize.x - 1) / ctx->blockSize.x); // at least enough threads

    ctx->h_results.resize(ctx->N);
    ALLOC(ctx->d_results, ctx->N * sizeof(Result));

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    sortByStartTime<<<ctx->gridSize, ctx->blockSize>>>(ctx->d_results, ctx->N);
}

void NO_OPTIMIZE best(Context *ctx) {
    correctSortByStartTime(ctx->h_results);
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;
    dim3 blockSize = dim3(1024);
    dim3 gridSize = dim3((TEST_SIZE + blockSize.x - 1) / blockSize.x); // at least enough threads

    std::vector<Result> h_results(TEST_SIZE), test(TEST_SIZE);
    Result *d_results;
    ALLOC(d_results, TEST_SIZE * sizeof(Result));

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        for (int i = 0; i < TEST_SIZE; i += 1) {
            h_results[i].startTime = rand() % 100;
            h_results[i].duration = rand() % 10 + 1;
            h_results[i].value = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
        }

        COPY_H2D(d_results, h_results.data(), TEST_SIZE * sizeof(Result));

        // compute correct result
        correctSortByStartTime(h_results);

        // compute test result
        sortByStartTime<<<gridSize, blockSize>>>(d_results, TEST_SIZE);
        SYNC();

        // copy back
        COPY_D2H(test.data(), d_results, TEST_SIZE * sizeof(Result));
        
        for (int i = 0; i < TEST_SIZE; i += 1) {
            if ((test[i].startTime != h_results[i].startTime) ||
                (test[i].duration != h_results[i].duration) ||
                (test[i].value != h_results[i].value)) {
                FREE(d_results);
                return false;
            }
        }
    }

    FREE(d_results);
    return true;
}

void destroy(Context *ctx) {
    FREE(ctx->d_results);
    delete ctx;
}
