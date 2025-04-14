// Driver for 54_stencil_game_of_life for Serial, OpenMP, MPI, and MPI+OpenMP
// /* Simulate one generation of Game of Life on `input`. Store the results in `output`.
//    A cell is 1 if it is alive and 0 if it is dead.
//    If a live cell has fewer than 2 live neighbors then it dies.
//    If a live cell has 2 or 3 live neighbors then it lives on.
//    If a live cell has more than 3 live neighbords then it dies.
//    If a cell is dead and has exactly 3 live neighbors then it becomes alive.
//    `input` and `output` are NxN grids stored in row-major.
//    Example:
//
//    input:  [[0, 0, 0, 0, 0],
//             [0, 1, 0, 0, 0],
//             [0, 1, 1, 0, 0],
//             [0, 0, 1, 1, 0],
//             [0, 1, 0, 0, 0]]
//    output: [[0, 0, 0, 0, 0],
//             [0, 1, 1, 0, 0],
//             [0, 1, 0, 1, 0],
//             [0, 0, 0, 1, 0],
//             [0, 0, 1, 0, 0]]
// */
// void gameOfLife(std::vector<int> const& input, std::vector<int> &output, size_t N) {

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

#include "utilities.hpp"
#include "baseline.hpp"
#include "generated-code.hpp"   // code generated by LLM

struct Context {
    std::vector<int> input, output;
    size_t N;
};

void reset(Context *ctx) {
    fillRand(ctx->input, 0, 2);
    std::fill(ctx->output.begin(), ctx->output.end(), 0);
    BCAST(ctx->input, INT);
}

Context *init() {
    Context *ctx = new Context();

    ctx->N = DRIVER_PROBLEM_SIZE;
    ctx->input.resize(ctx->N * ctx->N);
    ctx->output.resize(ctx->N * ctx->N);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    generated::gameOfLife(ctx->input, ctx->output, ctx->N);
}

void NO_OPTIMIZE best(Context *ctx) {
    baseline::gameOfLife(ctx->input, ctx->output, ctx->N);
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;

    std::vector<int> input(TEST_SIZE * TEST_SIZE), correct(TEST_SIZE * TEST_SIZE), test(TEST_SIZE * TEST_SIZE);

    int rank;
    GET_RANK(rank);

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        fillRand(input, 0, 2);
        std::fill(test.begin(), test.end(), 0);
        std::fill(correct.begin(), correct.end(), 0);
        BCAST(input, INT);

        // compute correct result
        baseline::gameOfLife(input, correct, TEST_SIZE);

        // compute test result
        generated::gameOfLife(input, test, TEST_SIZE);
        SYNC();

        bool isCorrect = true;
        if (IS_ROOT(rank)) {
            for (size_t i = 1; i < TEST_SIZE-1; i += 1) {
                for (size_t j = 1; j < TEST_SIZE-1; j += 1) {
                    if (test[i * TEST_SIZE + j] != correct[i * TEST_SIZE + j]) {
                        isCorrect = false;
                        break;
                    }
                }
                if (!isCorrect) {
                    break;
                }
            }
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
