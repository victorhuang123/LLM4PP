#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

ll baseline(ll N, ll K, const vector<ll>& a) {
    vector<vector<ll>> dp(N + 1, vector<ll>(K + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i < N; i++) {
        vector<ll> sum(K + 2, 0);
        for (int j = 0; j <= 100000; j++) {
            sum[j + 1] = (sum[j] + dp[i][j]) % MOD;
            sum[j + 1] %= MOD;
        }
        for (int j = 0; j <= K; j++) {
            ll min_val = max(0LL, j - a[i]);
            dp[i + 1][j] += (sum[j + 1] - sum[min_val] + MOD) % MOD;
            dp[i + 1][j] %= MOD;
        }
    }
    return dp[N][K];
}

vector<ll> generateInput(ll N, ll K) {
    vector<ll> a(N);
    for (ll i = 0; i < N; i++) {
        a[i] = rand() % (K + 1);
    }
    return a;
}