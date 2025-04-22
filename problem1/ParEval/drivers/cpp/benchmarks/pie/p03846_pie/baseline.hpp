#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

vector<int> generateInput(int N) {
    vector<int> A(N);
    rep(i, N) {
        if (N % 2) {
            if (i == 0) A[i] = 0;
            else A[i] = (i % 2 == 0) ? i : i - 1;
        } else {
            A[i] = (i % 2 == 0) ? i + 1 : i;
        }
    }
    return A;
}

ll baseline(int N, const vector<int>& A) {
    vector<int> B(100100, 0);
    rep1(i, N) {
        B[A[i-1]]++;
    }

    int OK = 1;
    if (N % 2) {
        if (B[0] != 1) OK = 0;
        rep1(i, N / 2) if (B[i * 2] != 2) OK = 0;
    }
    else {
        rep(i, N / 2) if (B[i * 2 + 1] != 2) OK = 0;
    }

    ll kotae = 1;
    ll mod = 1e9 + 7;
    rep(i, N / 2) {
        kotae = kotae * 2 % mod;
    }

    return OK ? kotae : 0;
}