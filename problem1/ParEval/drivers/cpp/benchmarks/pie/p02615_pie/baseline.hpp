#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll baseline(int N, vector<int>& A) {
    sort(A.begin(), A.end(), greater<int>());

    ll kotae = A[0];
    int K = N - 2;
    for (int p = 1; p < N; p++) {
        if (K > 0) {
            kotae += A[p];
            K--;
        }
        if (K > 0) {
            kotae += A[p];
            K--;
        }
    }

    return kotae;
}

vector<int> generate_input(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 1000000 + 1;
    }
    return A;
}