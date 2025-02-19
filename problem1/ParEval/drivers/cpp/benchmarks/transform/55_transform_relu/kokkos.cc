// Driver for 52_transform_relu
// /* Compute the ReLU function on every element of x. Elements less than zero become zero,
//    while elements greater than zero stay the same.
//    Use Kokkos to compute in parallel. Assume Kokkos has already been initialized.
//    Example:
// 
//    input: [-1.8, 24.0, 1.2, 0.0, -5.1, -0.2, 4.5]
//    output: [0, 24.0, 1.2, 0, 0, 0, 4.5]
// */
// void relu(Kokkos::View<double*> &x) {

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "kokkos-includes.hpp"

#include "utilities.hpp"
#include "baseline.hpp"
#include "generated-code.hpp"   // code generated by LLM


struct Context {
    Kokkos::View<double*> x;
    std::vector<double> vecX;
};

void reset(Context *ctx) {
    fillRandKokkos(ctx->x, -50.0, 50.0);
    fillRand(ctx->vecX, -50.0, 50.0);
}

Context *init() {
    Context *ctx = new Context();

    ctx->x = Kokkos::View<double*>("x", DRIVER_PROBLEM_SIZE);
    ctx->vecX.resize(DRIVER_PROBLEM_SIZE);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    relu(ctx->x);
}

void NO_OPTIMIZE best(Context *ctx) {
    correctRelu(ctx->vecX);
}

bool validate(Context *ctx) {

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int i = 0; i < numTries; i += 1) {
        std::vector<double> input(1024);
        fillRand(input, -50.0, 50.0);

        // compute correct result
        std::vector<double> correctResult = input;
        correctRelu(correctResult);

        // compute test result
        Kokkos::View<double*> testResult("testResult", input.size());
        copyVectorToView(input, testResult);

        relu(testResult);

        std::vector<double> testResultVec(input.size());
        copyViewToVector(testResult, testResultVec);
        
        if (!fequal(correctResult, testResultVec, 1e-5)) {
            return false;
        }
    }

    return true;
}

void destroy(Context *ctx) {
    delete ctx;
}


