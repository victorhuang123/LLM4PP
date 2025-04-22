#pragma once

#include <algorithm>
#include <vector>

using namespace std;

long long baseline(int n, int m) {
    vector<vector<long long>> dp(9, vector<long long>(n + 1));
    long long ans = 0, now;
    long long x, y, z;

    for (int i = 1; i <= n; i++) {
        x = i; y = i + 1; z = i + 2; // Example input generation
        dp[1][i] = x + y + z;
        dp[2][i] = x + y - z;
        dp[3][i] = x - y + z;
        dp[4][i] = -x + y + z;
        dp[5][i] = x - y - z;
        dp[6][i] = -x - y + z;
        dp[7][i] = -x + y - z;
        dp[8][i] = -x - y - z;
    }

    for (int i = 1; i <= 8; i++) {
        sort(dp[i].begin() + 1, dp[i].end(), greater<long long>());
        now = 0;
        for (int j = 1; j <= m; j++) {
            now += dp[i][j];
        }
        ans = max(ans, now);
    }

    return ans;
}