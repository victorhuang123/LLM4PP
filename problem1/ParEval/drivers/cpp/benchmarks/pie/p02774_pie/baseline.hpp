#pragma once

#include<bits/stdc++.h>

using namespace std;

#define rep(i,N) for(int i=0;i<(int64_t)N;i++)

typedef int64_t LL;

LL baseline(LL N, LL K, vector<LL>& A) {
    LL M, L = numeric_limits<LL>::min() / 3, R = LLONG_MAX / 3, count;
    bool minus;

    sort(A.begin(), A.end());

    while (R - L > 1) {
        M = (L + R) / 2, count = 0;
        rep(i, N) {
            int NG = i, OK = N;
            minus = (A.at(i) < 0) ? true : false;
            while (OK - NG > 1) {
                int BASE = (NG + OK) / 2;
                if (A.at(i) * A.at(BASE) <= M) (minus) ? OK = BASE : NG = BASE;
                else (minus) ? NG = BASE : OK = BASE;
            }
            count += (minus) ? N - OK : NG - i;
        }
        (count < K) ? L = M : R = M;
    }
    return R;
}

vector<LL> generateInput(LL N) {
    vector<LL> A(N);
    for (LL i = 0; i < N; ++i) {
        A[i] = i + 1;
    }
    return A;
}