#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

long long baseline(long long n) {
    long long m = (n + 1) * n / 2;
    double mn = 1e100;
    long long ind = 0;
    std::vector<long long> s(1266);

    for (int i = 0; i < m; i++) {
        long long z = rand() % (1LL << 30) + 1; // Example input generation
        if (z > (1LL << 62)) while (1);
        if (z % 2 == 0)
            s[ind++] = z;
        else mn = std::min(mn, z + 0.0);
    }
    std::sort(s.begin(), s.begin() + ind);
    if (ind != n) while (1);
    long long da = std::sqrt(s[0] * 1.0 * s[1] / mn) + 0.5;

    return da;
}

std::vector<long long> generateInput(long long n) {
    long long m = (n + 1) * n / 2;
    std::vector<long long> input(m);
    for (int i = 0; i < m; i++) {
        input[i] = rand() % (1LL << 30) + 1; // Example input generation
    }
    return input;
}