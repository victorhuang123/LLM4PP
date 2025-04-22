#pragma once

#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll baseline(int N, const vector<int>& A) {
    ll nokori = 1;
    vector<ll> B(N + 1);

    for (int i = 0; i <= N; ++i) {
        B[i] = nokori;
        nokori = (nokori - A[i]) * 2;
        if (nokori > 1e15) nokori = 1e15;
    }

    bool OK = true;
    ll kotae = 0;
    ll kari = 0;
    for (int i = N; i >= 0; --i) {
        if (B[i] < A[i]) OK = false;
        kari += A[i];
        kotae += min(kari, B[i]);
    }

    return OK ? kotae : -1;
}

vector<int> generateInput(int N) {
    vector<int> A(N + 1);
    for (int i = 0; i <= N; ++i) {
        A[i] = i + 1;
    }
    return A;
}