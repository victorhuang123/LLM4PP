#pragma once

#include <vector>

const long mod = 1e9 + 7;

long baseline(long N, long K) {
    long ans = 0;
    for (long k = K; k <= N + 1; k++) {
        long L = k * (k - 1) / 2;
        long R = N * k - k * (k - 1) / 2;
        ans = (ans + (R - L + 1)) % mod;
    }
    return ans % mod;
}

std::vector<long> generateInput() {
    return {1000000, 500000};
}