#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int baseline(int n, vector<vector<int>>& a) {
    vector<int> dp(1 << n, -1);

    function<int(int)> solve = [&](int msk) {
        if (msk == (1 << n) - 1)
            return 1;
        int in = __builtin_popcount(msk);
        int& res = dp[msk];
        if (res != -1)
            return res;
        res = 0;
        for (int i = 0; i < n; i++) {
            if (!((1 << i) & msk) && a[in][i]) {
                res = (1ll * res + solve(msk | (1 << i))) % MOD;
            }
        }
        return res;
    };

    return solve(0);
}

vector<vector<int>> generateInput(int n) {
    vector<vector<int>> a(n, vector<int>(n, 1));
    return a;
}