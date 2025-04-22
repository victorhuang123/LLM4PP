#pragma once

#include<bits/stdc++.h>
using namespace std;

int baseline(int K, const vector<int>& A) {
    int N = A.size();
    int saidai = K + A[0] - A[N - 1];
    for (int i = 0; i < N - 1; i++) {
        saidai = max(saidai, A[i + 1] - A[i]);
    }
    return K - saidai;
}

vector<int> generateInput(int K, int N) {
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = i;
    }
    return A;
}