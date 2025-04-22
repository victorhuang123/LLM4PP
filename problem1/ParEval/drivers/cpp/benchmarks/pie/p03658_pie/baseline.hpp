#pragma once

#include <vector>
#include <algorithm>

std::vector<int> generateInput(int N) {
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = N - i;
    }
    return A;
}

int baseline(int N, int K, std::vector<int>& A) {
    for(int i = 0; i < N - 1; i++) {
        for(int j = 0; j < N - i - 1; j++) {
            if(A[j] < A[j + 1]) {
                std::swap(A[j], A[j + 1]);
            }
        }
    }

    int b = 0;
    for (int i = 0; i < K; i++) {
        b += A[i];
    }

    return b;
}