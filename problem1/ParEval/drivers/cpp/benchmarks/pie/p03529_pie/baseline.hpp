#pragma once

#include <bits/stdc++.h>

#define rep(i,n) for(int i=0;i<n;i++)
#define LL long long
#define MOD 1000000007

using namespace std;

LL baseline(LL n, LL t) {
    vector<vector<LL>> dp(110, vector<LL>(10010, 0));
    LL all = 1, ans = 0;

    rep(i,n-1) all = all * (t + 1) % MOD;
    all = all * (t + 1) * t / 2 * n % MOD;
    dp[n][0] = 1;

    for(int i = n; i > 0; i--) {
        rep(j,10005) {
            rep(k,t+1) {
                if(dp[i][j] == 0) continue;
                if(k <= i) dp[i-1][j + (j + k) / i] = (dp[i-1][j + (j + k) / i] + dp[i][j]) % MOD;
                else dp[i-1][j] = (dp[i-1][j] + dp[i][j]) % MOD;
            }
        }
    }

    rep(i,10003) ans = (ans + i * dp[0][i]) % MOD;
    return (all - ans + MOD) % MOD;
}

vector<LL> generateInput() {
    return {100, 10000};
}