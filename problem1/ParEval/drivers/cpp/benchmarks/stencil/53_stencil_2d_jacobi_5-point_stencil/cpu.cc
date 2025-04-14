// Driver for 53_stencil_2d_jacobi_5-point_stencil for Serial, OpenMP, MPI, and MPI+OpenMP
// /* Compute one iteration of a 5-point 2D jacobi stencil on `input`. Store the results in `output`.
//    Each element of `input` will be averaged with its four neighbors and stored in the corresponding element of `output`.
//    i.e. output_{i,j} = (input_{i,j-1} + input_{i,j+1} + input_{i-1,j} + input_{i+1,j} + input_{i,j})/5
//    Replace with 0 when reading past the boundaries of `input`.
//    `input` and `output` are NxN grids stored in row-major.
//    Example:
//
//    input: [[3, 4, 1], [0, 1, 7], [5, 3, 2]]
//    output: [[1.4, 1.8, 2.4],[1.8, 3, 2.2], [1.6, 2.2, 2.4]]
// */
// void jacobi2D(std::vector<double> const& input, std::vector<double> &output, size_t N) {

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

#include "utilities.hpp"
#include "baseline.hpp"
#include "generated-code.hpp"   // code generated by LLM

struct Context {
    std::vector<double> input, output;
    size_t N;
};

void reset(Context *ctx) {
    fillRand(ctx->input, -100.0, 100.0);
    std::fill(ctx->output.begin(), ctx->output.end(), 0);
    BCAST(ctx->input, DOUBLE);
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
    generated::jacobi2D(ctx->input, ctx->output, ctx->N);
}

void NO_OPTIMIZE best(Context *ctx) {
    baseline::jacobi2D(ctx->input, ctx->output, ctx->N);
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;

    std::vector<double> input(TEST_SIZE * TEST_SIZE), correct(TEST_SIZE * TEST_SIZE), test(TEST_SIZE * TEST_SIZE);

    int rank;
    GET_RANK(rank);

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        fillRand(input, -100.0, 100.0);
        std::fill(test.begin(), test.end(), 0);
        std::fill(correct.begin(), correct.end(), 0);
        BCAST(input, DOUBLE);

        // compute correct result
        baseline::jacobi2D(input, correct, TEST_SIZE);

        // compute test result
        generated::jacobi2D(input, test, TEST_SIZE);
        SYNC();

        bool isCorrect = true;
        if (IS_ROOT(rank)) {
            for (size_t i = 1; i < TEST_SIZE-1; i += 1) {
                for (size_t j = 1; j < TEST_SIZE-1; j += 1) {
                    if (std::abs(test[i * TEST_SIZE + j] - correct[i * TEST_SIZE + j]) > 1e-6) {
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
