#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int baseline(int N, int K, vector<int>& A) {
    int L = 0, R = 1000000000;
    while (L + 1 < R) {
        int H = (L + R) / 2;
        ll k = 0;
        for (int i = 0; i < N; i++) {
            k += (A[i] - 1) / H;
        }
        if (k <= K) R = H;
        else L = H;
    }
    return R;
}

vector<int> generate_input(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 1000000000 + 1;
    }
    return A;
}