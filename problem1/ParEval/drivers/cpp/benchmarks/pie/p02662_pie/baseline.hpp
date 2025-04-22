#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353;

ll baseline(int N, int S, vector<int>& A) {
    ll dp[3001] = {0};
    sort(A.begin(), A.end());
    ll k2 = 1;
    for (int i = 0; i < mod - 2; i++) {
        k2 = (k2 * 2) % mod;
    }
    dp[0] = 1;
    for (int i = 0; i < N; i++) {
        dp[0] = (dp[0] * 2) % mod;
    }
    int s = 0;
    for (int i = 0; i < N; i++) {
        s = min(S, s + A[i]);
        for (int j = s; j >= A[i]; j--) {
            dp[j] = (dp[j] + dp[j - A[i]] * k2) % mod;
        }
    }
    return dp[S] % mod;
}

vector<int> generateInput(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = i + 1;
    }
    return A;
}