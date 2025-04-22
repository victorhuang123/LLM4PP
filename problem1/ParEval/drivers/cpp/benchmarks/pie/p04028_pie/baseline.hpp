#pragma once

#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 5005;
const int mod = 1e9 + 7;

int baseline(int n, const string &s) {
    vector<int> dp(N, 0), f(N, 0);

    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        fill(f.begin(), f.end(), 0);
        for (int j = 0; j <= i; j++) {
            f[j + 1] = (f[j + 1] + dp[j]) % mod;
            if (j) f[j - 1] = (f[j - 1] + 2 * dp[j]) % mod;
            else f[j] = (f[j] + dp[j]) % mod;
        }

        for (int j = 0; j < N; j++) dp[j] = f[j];
    }

    return dp[s.length()];
}

vector<int> generateInput() {
    int n = 5000;
    string s = string(5000, 'a');
    return {n, s};
}