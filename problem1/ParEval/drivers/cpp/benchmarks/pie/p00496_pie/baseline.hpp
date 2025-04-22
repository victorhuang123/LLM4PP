#pragma once

#include <vector>
#include <algorithm>

int baseline(int n, int t, int s, const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<std::vector<int>> dp(3005, std::vector<int>(2, 0));
    int cur = 0;
    int nex = 1;
    dp[0][cur] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3005; j++) dp[j][nex] = 0;

        for (int j = 0; j <= t; j++) {
            dp[j][nex] = std::max(dp[j][nex], dp[j][cur]);
        }

        for (int j = 0; j <= t - b[i]; j++) {
            if (j < s && s < j + b[i]) continue;
            dp[j + b[i]][nex] = std::max(dp[j + b[i]][nex], dp[j][cur] + a[i]);
        }

        cur = 1 - cur;
        nex = 1 - nex;
    }

    int ret = 0;
    for (int i = 0; i <= t; i++) ret = std::max(ret, dp[i][cur]);
    return ret;
}

std::vector<int> generateInput(int n) {
    std::vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = rand() % 1000 + 1;
        b[i] = rand() % 100 + 1;
    }
    return {a, b};
}