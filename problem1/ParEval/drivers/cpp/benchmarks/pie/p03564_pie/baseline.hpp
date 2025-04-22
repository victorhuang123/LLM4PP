#pragma once

#include <vector>

long long baseline(long long n, long long k) {
    long long a = 1;
    for (int i = 0; i < n; i++) {
        if (a * 2 < a + k) a *= 2;
        else a += k;
    }
    return a;
}

std::vector<long long> generateInput() {
    return {1000000000, 1000000000};
}