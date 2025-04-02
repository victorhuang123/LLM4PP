// Driver for 66_scan_longest_increaseing_subarray for CUDA and HIP
// /* Return the first longest increasing contiguous subarray in the vector x.
//    i.e. if x=[−2, 1, 2, 0, −1, 2, 3, −5, 4] then [-2, 1, 2], [-1, 2, 3] are both longest increasing contiguous
//    subarray, but [-2, 1, 2] is the first one, thus we return [-2, 1, 2] as the result.
//    Example:
// 
//    input: [−2, 1, 2, 0, −1, 2, 3, −5, 4]
//    output: [-2, 1, 2]
// */
// __global__ void longestIncreasingSubarray(std::vector<int> const& x, std::vector<int> &output) {

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "utilities.hpp"
#include "baseline.hpp"
#include "generated-code.cuh"   // code generated by LLM


struct Context {
    int *d_x, *d_output;
    std::vector<int> h_x, h_output;
    size_t N;
    dim3 blockSize, gridSize;
};

void reset(Context *ctx) {
    fillRand(ctx->h_x, -100, 100);

    COPY_H2D(ctx->d_x, ctx->h_x.data(), ctx->N * sizeof(int));
}

Context *init() {
    Context *ctx = new Context();

    ctx->N = DRIVER_PROBLEM_SIZE;
    ctx->blockSize = dim3(2048);
    ctx->gridSize = dim3((ctx->N + ctx->blockSize.x - 1) / ctx->blockSize.x); // at least enough threads

    ctx->h_x.resize(ctx->N);
    ctx->h_output.resize(ctx->N);
    ALLOC(ctx->d_x, ctx->N * sizeof(int));
    ALLOC(ctx->d_output, ctx->N * sizeof(int));

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    longestIncreasingSubarray<<<ctx->gridSize, ctx->blockSize>>>(ctx->d_x, ctx->d_output, ctx->N);
}

void NO_OPTIMIZE best(Context *ctx) {
    correctLongestIncreasingSubarray(ctx->h_x, ctx->h_output);
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;
    dim3 blockSize = dim3(1024);
    dim3 gridSize = dim3((TEST_SIZE + blockSize.x - 1) / blockSize.x); // at least enough threads

    std::vector<int> h_x(TEST_SIZE), correct(TEST_SIZE), test(TEST_SIZE);

    int *d_x, *d_output;
    ALLOC(d_x, TEST_SIZE * sizeof(int));
    ALLOC(d_output, TEST_SIZE * sizeof(int));

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        fillRand(h_x, -100, 100);
	    std::fill(correct.begin(), correct.end(), 0);

        COPY_H2D(d_x, h_x.data(), TEST_SIZE * sizeof(int));
        COPY_H2D(d_output, correct.data(), TEST_SIZE * sizeof(int));

        // compute correct result
        correctLongestIncreasingSubarray(h_x, correct);

        // compute test result
        longestIncreasingSubarray<<<gridSize, blockSize>>>(d_x, d_output, TEST_SIZE);
        SYNC();

        // copy back
        COPY_D2H(test.data(), d_output, TEST_SIZE * sizeof(int));

        if (!std::equal(correct.begin(), correct.end(), test.begin())) {
            FREE(d_x);
            FREE(d_output);
            return false;
        }
    }

    FREE(d_x);
    FREE(d_output);
    return true;
}

void destroy(Context *ctx) {
    FREE(ctx->d_x);
    FREE(ctx->d_output);
    delete ctx;
}
