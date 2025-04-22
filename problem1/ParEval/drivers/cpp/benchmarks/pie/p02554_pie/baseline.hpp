#pragma once

#include <vector>

const long long mod = 1e9 + 7;

long long baseline(long long n) {
    auto f = [](long long m, long long n) {
        long long ans = 1;
        while (n > 0) {
            if (n & 1)
                ans = (ans * m) % mod;
            m = (m * m) % mod;
            n = n >> 1;
        }
        return ans;
    };

    return (f(10, n) % mod - (2 * f(9, n)) % mod + f(8, n) % mod + mod) % mod;
}

std::vector<long long> generateInput() {
    return {1000000000}; // Example input to maximize the problem scale
}