#pragma once

#include <vector>

std::vector<int> generateInput() {
    int N = 200000;
    long long K = 1000000000000LL;
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = (i + 1) % N + 1;
    }
    return A;
}

int baseline(int N, long long K, const std::vector<int>& A) {
    std::vector<int> check(N, -1);
    std::vector<int> move(N, 0);

    for (int i = 0; i < N; ++i) {
        check[i] = -A[i];
    }

    int i = 0, j = 0;
    while (true) {
        if (check[i] < 0) {
            check[i] = j;
            move[j] = i;
        } else {
            break;
        }
        i = A[i] - 1;
        j++;
    }

    if (K >= j) {
        K = (K - check[i]) % (j - check[i]) + check[i];
    }

    return move[K] + 1;
}