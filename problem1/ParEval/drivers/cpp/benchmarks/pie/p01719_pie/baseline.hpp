#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll baseline(int n, int d, int x, vector<vector<ll>>& p) {
    for (int i = 1; i < d; i++) {
        vector<ll> dp(100001, -1);
        dp[x] = x;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= 100000 - p[i][j]; k++) {
                if (dp[k] >= p[i - 1][j]) {
                    dp[k + p[i][j] - p[i - 1][j]] = max(dp[k + p[i][j] - p[i - 1][j]], dp[k] - p[i - 1][j]);
                }
            }
        }
        int ma = 0;
        for (int k = 0; k <= 100000; k++) {
            if (dp[k] >= 0) {
                ma = k;
            }
        }
        x = ma;
    }
    return x;
}

vector<vector<ll>> generateInput(int n, int d) {
    vector<vector<ll>> p(d, vector<ll>(n));
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < n; j++) {
            p[i][j] = rand() % 100000 + 1;
        }
    }
    return p;
}