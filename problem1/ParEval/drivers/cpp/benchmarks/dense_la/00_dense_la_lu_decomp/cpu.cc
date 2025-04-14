// Driver for 00_dense_la_lu_decomp for Serial, OpenMP, MPI, and MPI+OpenMP
// /* Factorize the matrix A into A=LU where L is a lower triangular matrix and U is an upper triangular matrix.
//    Store the results for L and U into the original matrix A. 
//    A is an NxN matrix stored in row-major.
//    Example:
// 
//    input: [[4, 3], [6, 3]]
//    output: [[4, 3], [1.5, -1.5]]
// */
// void luFactorize(std::vector<double> &A, size_t N) {

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

#include "utilities.hpp"
#include "baseline.hpp"
#include "generated-code.hpp"   // code generated by LLM

struct Context {
    std::vector<double> A;
    size_t N;
};

void reset(Context *ctx) {
    fillRand(ctx->A, -10.0, 10.0);
    BCAST(ctx->A, DOUBLE);
}

Context *init() {
    Context *ctx = new Context();

    ctx->N = DRIVER_PROBLEM_SIZE;
    ctx->A.resize(ctx->N * ctx->N);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    generated::luFactorize(ctx->A, ctx->N);
}

void NO_OPTIMIZE best(Context *ctx) {
    baseline::luFactorize(ctx->A, ctx->N);
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 512;

    std::vector<double> A(TEST_SIZE * TEST_SIZE);
    std::vector<double> A_correct(TEST_SIZE * TEST_SIZE);
    std::vector<double> A_test(TEST_SIZE * TEST_SIZE);

    int rank;
    GET_RANK(rank);

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int trialIter = 0; trialIter < numTries; trialIter += 1) {
        // set up input
        fillRand(A, -10.0, 10.0);
        BCAST(A, DOUBLE);

        // compute correct result
        A_correct = A;
        baseline::luFactorize(A_correct, TEST_SIZE);

        // compute test result
        A_test = A;
        generated::luFactorize(A_test, TEST_SIZE);
        SYNC();
        
        bool isCorrect = true;
        if (IS_ROOT(rank) && !fequal(A_correct, A_test, 1e-3)) {
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
