// Driver for 05_fft_inverse_fft for Kokkos
// #include <Kokkos_Core.hpp>
// 
// /* forward declare fft. computes fourier transform in-place */
// void fft(Kokkos::View<Kokkos::complex<double>*> &x);
// 
// /* Compute the inverse fourier transform of x in-place.
//    Use Kokkos to compute in parallel. Assume Kokkos has already been initialized.
//    Example:
//    
//    input: [1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0]
//    output: [{0.5,0}, {0.125,0.301777}, {0,-0}, {0.125,0.0517767}, {0,-0}, {0.125,-0.0517767}, {0,-0}, {0.125,-0.301777}]
// */
// void ifft(Kokkos::View<Kokkos::complex<double>*> &x) {

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "kokkos-includes.hpp"

#include "utilities.hpp"
#include "baseline.hpp"
#include "generated-code.hpp"   // code generated by LLM

struct Context {
    Kokkos::View<Kokkos::complex<double>*> x;
    std::vector<double> real, imag;
    std::vector<std::complex<double>> x_host;
};

void reset(Context *ctx) {
    fillRand(ctx->real, -1.0, 1.0);
    fillRand(ctx->imag, -1.0, 1.0);

    for (int i = 0; i < ctx->x.size(); i += 1) {
        ctx->x_host[i] = std::complex<double>(ctx->real[i], ctx->imag[i]);
        ctx->x(i) = Kokkos::complex<double>(ctx->real[i], ctx->imag[i]);
    }
}

Context *init() {
    Context *ctx = new Context();

    ctx->x = Kokkos::View<Kokkos::complex<double>*>("x", DRIVER_PROBLEM_SIZE);
    ctx->real.resize(DRIVER_PROBLEM_SIZE);
    ctx->imag.resize(DRIVER_PROBLEM_SIZE);
    ctx->x_host.resize(DRIVER_PROBLEM_SIZE);

    reset(ctx);
    return ctx;
}

void NO_OPTIMIZE compute(Context *ctx) {
    ifft(ctx->x);
}

void NO_OPTIMIZE best(Context *ctx) {
    correctIfft(ctx->x_host);
}

bool validate(Context *ctx) {
    const size_t TEST_SIZE = 1024;

    const size_t numTries = MAX_VALIDATION_ATTEMPTS;
    for (int i = 0; i < numTries; i += 1) {
        // set up input
        std::vector<double> real(TEST_SIZE), imag(TEST_SIZE);
        std::vector<std::complex<double>> x_host(TEST_SIZE);
        Kokkos::View<Kokkos::complex<double>*> x("x", TEST_SIZE);

        fillRand(real, -1.0, 1.0);
        fillRand(imag, -1.0, 1.0);

        for (int j = 0; j < x.size(); j += 1) {
            x_host[j] = std::complex<double>(real[j], imag[j]);
            x(j) = Kokkos::complex<double>(real[j], imag[j]);
        }

        // compute correct result
        std::vector<std::complex<double>> correct = x_host;
        correctIfft(correct);

        // compute test result
        Kokkos::View<Kokkos::complex<double>*> test = x;
        ifft(test);
        
        for (int j = 0; j < test.size(); j += 1) {
            auto const& correctVal = correct[j];
            auto const& testVal = test(j);
            if (std::abs(correctVal.real() - testVal.real()) > 1e-4 || std::abs(correctVal.imag() - testVal.imag()) > 1e-4) {
                return false;
            }
        }
    }

    return true;
}

void destroy(Context *ctx) {
    delete ctx;
}
