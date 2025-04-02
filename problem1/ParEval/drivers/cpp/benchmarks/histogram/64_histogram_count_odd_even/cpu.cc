// Driver for 64_histogram_count_odd_even for Serial, OpenMP, MPI, and MPI+OpenMP
// /* Count the number of odd and even numbers in a given integer vector x
//    Examples:
// 
//    input: [7, 4, 3, 2, 1]
//    output: [3, 2]
// 
//    input: [5, 3, 2 1]
//    output: [3, 1]
// */
// void NO_INLINE correctCountOddEven(std::vector<int> const& x, std::array<size_t, 2> &bins) {

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
    std::array<size_t, 2> bins;
};

void reset(Context *ctx) {
    fillRand(ctx->x, 0, 10000);
    BCAST(ctx->x, INT);
    ctx->bins.fill(0);
}

Context *init() {
    Context *ctx = new Context();

    ctx->x.resize(DRIVER_PROBLEM_SIZE);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    countOddEven(ctx->x, ctx->bins);
}

void NO_OPTIMIZE best(Context *ctx) {
    correctCountOddEven(ctx->x, ctx->bins);
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;

    std::vector<int> x(TEST_SIZE);
    std::array<size_t, 2> correct, test;

    int rank;
    GET_RANK(rank);

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int i = 0; i < numTries; i += 1) {
        // set up input
        fillRand(x, 0, 10000);
        BCAST(x, int);
        correct.fill(0);
        test.fill(0);

        // compute correct result
        correctCountOddEven(x, correct);

        // compute test result
        countOddEven(x, test);
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
