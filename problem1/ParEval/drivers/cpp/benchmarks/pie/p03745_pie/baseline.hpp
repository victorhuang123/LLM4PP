#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int n, const vector<int>& aa) {
    vector<vector<int>> dp(n + 1, vector<int>(2, INT_MAX));
    dp[1][0] = dp[1][1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[i-1][0] + (aa[i-1] < aa[i-2]);
        dp[i][1] = dp[i-1][1] + (aa[i-1] > aa[i-2]);
        dp[i][0] = min(dp[i][0], dp[i-1][1] + 1);
        dp[i][1] = min(dp[i][1], dp[i-1][0] + 1);
    }

    return min(dp[n][0], dp[n][1]);
}

vector<int> generateInput(int n) {
    vector<int> aa(n);
    for (int i = 0; i < n; i++) {
        aa[i] = i + 1;
    }
    return aa;
}