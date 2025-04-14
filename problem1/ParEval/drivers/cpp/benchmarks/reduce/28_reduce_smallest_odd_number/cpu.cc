// Driver for 28_reduce_smallest_odd_number for Serial, OpenMP, MPI, and MPI+OpenMP
// /* Return the value of the smallest odd number in the vector x.
//    Examples:
//
//    input: [7, 9, 5, 2, 8, 16, 4, 1]
//    output: 1
//
//    input: [8, 36, 7, 2, 11]
//    output: 7
// */
// int smallestOdd(std::vector<int> const& x) {

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
    fillRand(ctx->x, 0.0, 100.0);
    BCAST(ctx->x, INT);
}

Context *init() {
    Context *ctx = new Context();

    ctx->x.resize(DRIVER_PROBLEM_SIZE);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    int val = generated::smallestOdd(ctx->x);
    (void)val;
}

void NO_OPTIMIZE best(Context *ctx) {
    int val = baseline::smallestOdd(ctx->x);
    (void)val;
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;

    std::vector<int> x(TEST_SIZE);
    int test, correct;

    int rank;
    GET_RANK(rank);

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        fillRand(x, 0.0, 100.0);
        BCAST(x, INT);

        // compute correct result
        correct = baseline::smallestOdd(x);

        // compute test result
        test = generated::smallestOdd(x);
        SYNC();

        bool isCorrect = true;
        if (IS_ROOT(rank) && correct != test) {
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
