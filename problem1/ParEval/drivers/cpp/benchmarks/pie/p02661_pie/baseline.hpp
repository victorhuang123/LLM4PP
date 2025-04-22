#pragma once

#include<bits/stdc++.h>
using namespace std;

int baseline(int N, vector<int>& A, vector<int>& B) {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    if (N % 2) {
        int a = A[(N - 1) / 2];
        int b = B[(N - 1) / 2];
        return b - a + 1;
    }
    else {
        int a = A[N / 2] + A[N / 2 - 1];
        int b = B[N / 2] + B[N / 2 - 1];
        return b - a + 1;
    }
}

vector<int> generateInput(int N) {
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 1000000;
        B[i] = rand() % 1000000;
    }
    return {A, B};
}