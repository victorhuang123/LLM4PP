#pragma once
#include <vector>
#include <cmath>
#include <complex>

/* Compute the fourier transform of x. Store real part of results in r and imaginary in i.
   Example:

   input: [1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0]
   output: r: [4, 1, 0, 1, 0, 1, 0, 1] i: [0, -2.41421, 0, -0.414214, 0, 0.414214, 0, 2.41421]
*/
void NO_INLINE correctFft(std::vector<std::complex<double>> const& x, std::vector<double> &r, std::vector<double> &i) {
	std::vector<std::complex<double>> x_copy = x;
	// DFT
	unsigned int N = x_copy.size(), k = N, n;
	double thetaT = 3.14159265358979323846264338328L / N;
	std::complex<double> phiT = std::complex<double>(std::cos(thetaT), -std::sin(thetaT)), T;
	while (k > 1) {
		n = k;
		k >>= 1;
		phiT = phiT * phiT;
		T = 1.0L;
		for (unsigned int l = 0; l < k; l++)
		{
			for (unsigned int a = l; a < N; a += n)
			{
				unsigned int b = a + k;
				std::complex<double> t = x_copy[a] - x_copy[b];
				x_copy[a] += x_copy[b];
				x_copy[b] = t * T;
			}
			T *= phiT;
		}
	}
	// Decimate
	unsigned int m = (unsigned int)std::log2(N);
	for (unsigned int a = 0; a < N; a++)
	{
		unsigned int b = a;
		// Reverse bits
		b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
		b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
		b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
		b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
		b = ((b >> 16) | (b << 16)) >> (32 - m);
		if (b > a)
		{
			std::complex<double> t = x_copy[a];
			x_copy[a] = x_copy[b];
			x_copy[b] = t;
		}
	}

   // split into real and imaginary parts
   for (size_t j = 0; j < x_copy.size(); j += 1) {
      r[j] = x_copy[j].real();
      i[j] = x_copy[j].imag();
   }
}

void fftCooleyTookey(std::vector<std::complex<double>> &x) {
    const size_t N = x.size();
    if (N <= 1) return;

    // divide
    std::vector<std::complex<double>> even = std::vector<std::complex<double>>(N/2);
	std::vector<std::complex<double>> odd = std::vector<std::complex<double>>(N/2);

	for (size_t j = 0; j < N/2; ++j) {
		even[j] = x[j*2];
		odd[j] = x[j*2+1];
	}

    // conquer
    fftCooleyTookey(even);
    fftCooleyTookey(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k) {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

#if defined(USE_CUDA)
// a lot of model outputs assume this is defined for some reason, so just define it
__device__ DOUBLE_COMPLEX_T cexp(DOUBLE_COMPLEX_T arg) {
   DOUBLE_COMPLEX_T res;
   float s, c;
   float e = expf(arg.x);
   sincosf(arg.y, &s, &c);
   res.x = c * e;
   res.y = s * e;
   return res;
}

__device__ DOUBLE_COMPLEX_T cuCexp(DOUBLE_COMPLEX_T arg) {
   return cexp(arg);
}

__device__ DOUBLE_COMPLEX_T hipCexp(DOUBLE_COMPLEX_T arg) {
   return cexp(arg);
}
#endif