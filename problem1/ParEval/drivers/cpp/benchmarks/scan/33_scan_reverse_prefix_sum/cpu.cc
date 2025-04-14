// Driver for 33_scan_reverse_prefix_sum for Serial, OpenMP, MPI, and MPI+OpenMP
// /* Compute the reverse prefix sum of the vector x into output.
//    Examples:
//
//    input: [1, 7, 4, 6, 6, 2]
//    output: [2, 8, 14, 18, 25, 26]
//
//    input: [3, 3, 7, 1, -2]
//    output: [-2, -1, 6, 9, 12]
// */
// void reversePrefixSum(std::vector<int> const& x, std::vector<int> &output) {

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

#include "utilities.hpp"
#include "baseline.hpp"
#include "generated-code.hpp"   // code generated by LLM

struct Context {
    std::vector<int> x;
    std::vector<int> output;
};

void reset(Context *ctx) {
    fillRand(ctx->x, -100, 100);
    BCAST(ctx->x, INT);
}

Context *init() {
    Context *ctx = new Context();

    ctx->x.resize(DRIVER_PROBLEM_SIZE);
    ctx->output.resize(DRIVER_PROBLEM_SIZE);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    generated::reversePrefixSum(ctx->x, ctx->output);
}

void NO_OPTIMIZE best(Context *ctx) {
    baseline::reversePrefixSum(ctx->x, ctx->output);
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;

    std::vector<int> x(TEST_SIZE), correct(TEST_SIZE), test(TEST_SIZE);

    int rank;
    GET_RANK(rank);

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        fillRand(x, -100, 100);
        BCAST(x, INT);

        // compute correct result
        baseline::reversePrefixSum(x, correct);

        // compute test result
        generated::reversePrefixSum(x, test);
        SYNC();

        bool isCorrect = true;
        if (IS_ROOT(rank) && !std::equal(correct.begin(), correct.end(), test.begin())) {
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
