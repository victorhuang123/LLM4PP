#pragma once

#include <vector>

std::vector<long long> baseline(int N, int M, int L, int R, const std::vector<int>& s, const std::vector<int>& t, const std::vector<int>& e, const std::vector<int>& c) {
    std::vector<long long> d(N, 0);

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < N; j++) d[j] = 0;

        for (int j = 0; j < R; j++) d[s[j]] += c[t[j]] * e[j];
    }

    return d;
}

std::vector<int> generateInput(int size, int value) {
    std::vector<int> input(size, value);
    return input;
}