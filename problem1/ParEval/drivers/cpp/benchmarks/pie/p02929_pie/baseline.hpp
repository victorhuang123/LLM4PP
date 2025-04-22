#pragma once

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 100001;

int dp[2 * N], mod = 1e9 + 7;

int baseline(int n, vector<int>& a) {
    memset(dp, -1, sizeof dp);
    function<int(int, int)> solve = [&](int idx, int open) {
        if (idx == 2 * n) return open == 0;
        if (open < 0) return 0;
        if (dp[idx] != -1) return dp[idx];
        if (((open & 1) ^ a[idx]) == 0) return 1LL * open * solve(idx + 1, open - 1) % mod;
        return solve(idx + 1, open + 1);
    };
    int ans = solve(0, 0);
    for (int i = 1; i <= n; i++) {
        ans = 1LL * ans * i % mod;
    }
    return ans;
}

vector<int> generateInput(int n) {
    return vector<int>(2 * n, 0);
}