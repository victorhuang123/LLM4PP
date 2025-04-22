#pragma once

#include <vector>
#include <algorithm>

double baseline(int N, int K, const std::vector<int>& P) {
    long long saidai = 0;
    long long ima = 0;
    for (int i = 0; i < K; i++) ima += P[i] + 1;
    saidai = ima;

    for (int i = K; i < N; i++) {
        ima += P[i] + 1;
        ima -= P[i - K] + 1;
        saidai = std::max(saidai, ima);
    }

    double kotae = saidai * 0.5;
    return kotae;
}

std::vector<int> generateInput(int N) {
    std::vector<int> P(N);
    for (int i = 0; i < N; i++) {
        P[i] = i + 1;
    }
    return P;
}