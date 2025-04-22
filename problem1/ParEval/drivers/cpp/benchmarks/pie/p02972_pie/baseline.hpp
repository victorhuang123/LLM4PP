#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

vector<int> baseline(int N, vector<int>& A) {
    vector<int> kotae;
    vector<int> B(N + 1, 0);

    for (int i = N; i > 0; i--) {
        if (A[i] != B[i]) {
            kotae.pb(i);
            int rt = sqrt(i);
            rep1(j, rt) {
                if (i % j == 0) {
                    B[j] ^= 1;
                    if(i != j * j) B[i / j] ^= 1;
                }
            }
        }
    }
    return kotae;
}

vector<int> generateInput(int N) {
    vector<int> A(N + 1);
    rep1(i, N) {
        A[i] = i % 2;
    }
    return A;
}