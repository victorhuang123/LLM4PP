// Driver for 65_reduce_array_to_half for Serial, OpenMP, MPI, and MPI+OpenMP
// /* Given an integer array x. You can choose a set of integers and remove all the occurrences of these integers in the array.
//    Return the minimum size of the set so that at least half of the integers of the array are removed.
//    Example:
// 
//    input: x=[[3, 3, 3, 3, 5, 5, 5, 2, 2, 7]
//    output: 2
//    explanation: Choosing {3,7} will make the new array [5,5,5,2,2] which has size 5 (i.e equal to half of the size of the old array).
// Possible sets of size 2 are {3,5},{3,2},{5,2}.
// Choosing set {2,7} is not possible as it will make the new array [3,3,3,3,5,5,5] which has a size greater than half of the size of the old array.
// 
//    input: x = [7,7,7,7,7,7]
//    output: 1
//    explanation: The only possible set you can choose is {7}. This will make the new array empty.
// */
// int NO_INLINE correctReduceArrayToHalf(std::vector<int> const& x) {

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
    int val = correctReduceArrayToHalf(ctx->x);
    (void)val;
}

void NO_OPTIMIZE best(Context *ctx) {
    int val = correctCorrectReduceArrayToHalf(ctx->x);
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
        fillRand(x, 0, 100);
        BCAST(x, INT);

        // compute correct result
        correct = correctCorrectReduceArrayToHalf(x);

        // compute test result
        test = correctReduceArrayToHalf(x);
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
