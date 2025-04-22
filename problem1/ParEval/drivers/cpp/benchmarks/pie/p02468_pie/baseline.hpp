#pragma once

#include <vector>

long long baseline(long long a, long long b) {
    const long long mod = 1000000007;
    long long a1 = a % mod;
    long long p = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            p *= a1;
            p = p % mod;
        }
        b /= 2;
        a1 = (a1 * a1) % mod;
    }
    return p;
}

std::vector<long long> generateInput() {
    return {123456789, 987654321};
}