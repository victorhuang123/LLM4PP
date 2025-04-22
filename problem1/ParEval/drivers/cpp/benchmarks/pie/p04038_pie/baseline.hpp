#pragma once

#include<bits/stdc++.h>

#define int long long

using namespace std;

const int mod = 1e9 + 7;

int baseline(int n, int k) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<int> fac(n * k + 1), rfac(n * k + 1);

    auto pw = [](int a, int b) {
        int ret = 1;
        for (; b; b >>= 1, a = 1ll * a * a % mod)
            if (b & 1)
                ret = 1ll * ret * a % mod;
        return ret;
    };

    auto c = [&](int a, int b) {
        return 1ll * fac[b] * rfac[a] % mod * rfac[b - a] % mod;
    };

    dp[0][0] = 1;
    fac[0] = rfac[0] = 1;
    for (int i = 1; i <= n * k; i++) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
        rfac[i] = 1ll * rfac[i - 1] * pw(i, mod - 2) % mod;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++) {
            if (j)
                dp[i][j] = dp[i][j - 1];
            dp[i][j] = (dp[i][j] + (1ll * dp[i - 1][j] * c(k - 2, i * (k - 1) + j - 1) % mod)) % mod;
        }

    if (k == 1)
        return 1;
    else
        return 1ll * dp[n][n] * fac[n] % mod;
}

vector<int> generateInput() {
    return {2000, 2000};
}