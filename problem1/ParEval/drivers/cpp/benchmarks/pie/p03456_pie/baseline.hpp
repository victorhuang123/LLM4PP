#pragma once

#include <vector>
#include <cmath>

int baseline(long long a, long long b) {
    int s = 0;
    long long n = b;
    while (b) {
        s++;
        b /= 10;
    }
    for (int i = 1; i <= s; i++) {
        a *= 10;
    }
    n += a;
    long long sqrt_n = sqrt(n);
    return (sqrt_n * sqrt_n == n) ? 1 : 0;
}

std::pair<long long, long long> generateInput() {
    return {1234567890123456789, 9876543210987654321};
}