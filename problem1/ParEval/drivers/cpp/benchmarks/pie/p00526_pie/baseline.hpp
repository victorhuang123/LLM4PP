#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> generateInput(int n) {
    vector<int> a(n + 2);
    for (int i = 1; i <= n; i++) {
        a[i] = rand() % 2;
    }
    return a;
}

int baseline(int n, vector<int>& a) {
    vector<vector<int>> dp(n + 2, vector<int>(3, 0));

    a[0] = a[1] ^ 1;
    a[n + 1] = a[n] ^ 1;

    for (int i = 1; i <= n; i++) {
        if (a[i - 1] ^ a[i]) {
            dp[i][0] = dp[i - 1][0] + 1;
            dp[i][1] = dp[i - 1][1] + 1;
            dp[i][2] = dp[i - 1][2] + 1;
        } else {
            dp[i][0] = 1;
            dp[i][1] = dp[i - 1][0] + 1;
            dp[i][2] = dp[i - 1][1] + 1;
        }
    }

    int maxVal = 0;
    for (int i = 0; i <= n; i++) {
        maxVal = max(maxVal, *max_element(dp[i].begin(), dp[i].end()));
    }
    return maxVal;
}