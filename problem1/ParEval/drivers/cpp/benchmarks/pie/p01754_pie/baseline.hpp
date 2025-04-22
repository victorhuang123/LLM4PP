#pragma once

#include <vector>
#include <algorithm>

using namespace std;

long long baseline(long long N, long long P, long long Q, vector<long long>& C) {
    long long zenbugaishoku = 0;

    for (int i = 0; i < N; i++) {
        zenbugaishoku += C[i];
    }

    vector<long long> A(N);

    for (int i = 0; i < N; i++) {
        A[i] = C[i] - (Q - i) * P;
    }

    sort(A.begin(), A.end());

    long long Answer = zenbugaishoku;
    long long sum = zenbugaishoku;

    for (int i = 0; i < N; i++) {
        sum -= A[i];
        sum += 2 * i * P;
        Answer = max(sum, Answer);
    }

    return Answer;
}

vector<long long> generateInput(long long N, long long P, long long Q) {
    vector<long long> C(N, 1000000000);
    return C;
}