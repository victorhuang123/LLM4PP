// Driver for 68_median for Serial, OpenMP, MPI, and MPI+OpenMP
// /* Given a vector x, please return its Median. The Median is the middle value in an ordered integer vector. If the size of the vector is even, there is no middle value, and the median is the mean of the two middle values.
//   Example:
//
//   input: [2, 3, 4]
//   output: 3
//
//   input: [2, 3]
//   output: 2.5
// */
// float median(std::vector<int> &x) {

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
};

void reset(Context *ctx) {
    fillRand(ctx->x, 0, 10000);
    BCAST(ctx->x, INT);
}

Context *init() {
    Context *ctx = new Context();

    ctx->x.resize(DRIVER_PROBLEM_SIZE);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    float sm = generated::median(ctx->x);
    (void)sm;
}

void NO_OPTIMIZE best(Context *ctx) {
    float sm = baseline::median(ctx->x);
    (void)sm;
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;

    std::vector<int> x(TEST_SIZE);

    int rank;
    GET_RANK(rank);

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        fillRand(x, 0, 10000);
        BCAST(x, INT);

        // compute correct result
        float correct = baseline::median(x);

        // compute test result
        float test = generated::median(x);
        SYNC();
        bool isCorrect = true;
        if (IS_ROOT(rank) && std::fabs(correct - test) > 1e-5 ) {
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
