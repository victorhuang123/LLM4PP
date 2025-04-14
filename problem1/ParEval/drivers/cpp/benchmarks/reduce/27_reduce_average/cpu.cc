// Driver for 27_reduce_average for Serial, OpenMP, MPI, and MPI+OpenMP
// /* Return the average of the vector x.
//    Examples:
//
//    input: [1, 8, 4, 5, 1]
//    output: 3.8
//
//    input: [2, 2, 2, 3]
//    output: 2.25
// */
// double average(std::vector<double> const& x) {

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

#include "utilities.hpp"
#include "baseline.hpp"
#include "generated-code.hpp"   // code generated by LLM

struct Context {
    std::vector<double> x;
};

void reset(Context *ctx) {
    fillRand(ctx->x, 0.0, 100.0);
    BCAST(ctx->x, DOUBLE);
}

Context *init() {
    Context *ctx = new Context();

    ctx->x.resize(DRIVER_PROBLEM_SIZE);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    double val = generated::average(ctx->x);
    (void)val;
}

void NO_OPTIMIZE best(Context *ctx) {
    double val = baseline::average(ctx->x);
    (void)val;
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;

    std::vector<double> x(TEST_SIZE);
    double test, correct;

    int rank;
    GET_RANK(rank);

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        fillRand(x, 0.0, 100.0);
        BCAST(x, DOUBLE);

        // compute correct result
        correct = baseline::average(x);

        // compute test result
        test = generated::average(x);
        SYNC();

        bool isCorrect = true;
        if (IS_ROOT(rank) && std::abs(correct - test) > 1e-4) {
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
