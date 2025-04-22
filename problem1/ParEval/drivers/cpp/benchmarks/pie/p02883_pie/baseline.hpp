#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> generate_input(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 1000000 + 1;
    }
    return A;
}

ll baseline(ll N, ll K, vector<int>& A, vector<int>& F) {
    sort(A.begin(), A.end());
    sort(F.begin(), F.end());
    reverse(F.begin(), F.end());

    ll L = -1, R = 1e18;
    while (L + 1 < R) {
        ll M = (L + R) / 2;

        ll kazu = 0;
        for (int i = 0; i < N; i++) {
            if ((ll)A[i] * F[i] > M) {
                kazu += ((ll)A[i] * F[i] - M + F[i] - 1) / F[i];
            }
        }
        if (kazu <= K) R = M;
        else L = M;
    }

    return R;
}