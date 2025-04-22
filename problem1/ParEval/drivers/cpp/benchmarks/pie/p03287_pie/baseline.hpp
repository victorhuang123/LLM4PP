#pragma once

#include<bits/stdc++.h>
using namespace std;

#define repeat(i, n) for(int i = 0; i < (n); i++)

long long baseline(int N, int M, vector<int>& A) {
    vector<long long> B(N + 1, 0);
    map<int, int> MAP;

    repeat(i, N) {
        B[i + 1] = B[i] + A[i];
        B[i + 1] %= M;
        MAP[(int)B[i + 1]]++;
    }
    MAP[0]++;

    long long result = 0;
    for (auto ITR : MAP) {
        result += 1ll * ITR.second * (ITR.second - 1) / 2;
    }

    return result;
}

vector<int> generateInput(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 1000000 + 1;
    }
    return A;
}