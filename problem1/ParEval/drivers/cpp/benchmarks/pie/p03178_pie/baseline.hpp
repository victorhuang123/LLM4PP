#pragma once

#include <bits/stdc++.h>
using namespace std;

int mod = 1e9 + 7;
int dp[10004][3][101];

int solve(int i, int t, int cnt, const string& x, int d) {
    if (i == x.size() - 1) {
        if (cnt) return 0;
        return 1;
    }

    if (dp[i][t][cnt] != -1) return dp[i][t][cnt];

    int v = 0;

    for (int j = 0; j < 10; j++) {
        if (t == 0 && j == x[i + 1] - 48) v = (v + solve(i + 1, 0, (cnt + j) % d, x, d)) % mod;
        else if (t == 0 && j > x[i + 1] - 48) break;
        else v = (v + solve(i + 1, 1, (cnt + j) % d, x, d)) % mod;
    }

    return dp[i][t][cnt] = v;
}

int baseline(const string& x, int d) {
    memset(dp, -1, sizeof dp);
    int ans = -1;
    int first = x[0] - 48;

    for (int i = 0; i < first; i++) ans = (ans + solve(0, 1, i % d, x, d)) % mod;
    ans = (ans + solve(0, 0, first % d, x, d)) % mod;

    return ans % mod;
}

string generateInput() {
    return "99999999999999999999999999999999999999999999999999";
}