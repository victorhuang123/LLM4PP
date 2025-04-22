#pragma once

#include<vector>
#include<algorithm>

int baseline(int s, int d, int m, const std::vector<int>& k, const std::vector<std::vector<int>>& w, const std::vector<std::vector<int>>& p, const std::vector<int>& f) {
    std::vector<int> dp(m + 1, -1);
    dp[0] = 0;

    for (int i = 0; i < d; i++) {
        for (int x = 0; x < k[f[i]]; x++) {
            int v = p[f[i]][x], c = w[f[i]][x];
            for (int j = m - v; j >= 0; j--) {
                if (dp[j] >= 0) dp[j + v] = std::max(dp[j + v], dp[j] + c);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        if (dp[i] > dp[ans]) ans = i;
    }
    return dp[ans];
}

std::vector<std::vector<int>> generateInput(int s, int d, int m, std::vector<int>& k, std::vector<int>& f) {
    std::vector<std::vector<int>> w(s, std::vector<int>(55, 0));
    std::vector<std::vector<int>> p(s, std::vector<int>(55, 0));

    for (int i = 0; i < s; i++) {
        k[i] = 55;
        for (int j = 0; j < 55; j++) {
            w[i][j] = rand() % 100;
            p[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < d; i++) {
        f[i] = rand() % s;
    }

    return {w, p};
}