#pragma once

#include <vector>
#include <algorithm>

using namespace std;

double baseline(int n, int m, vector<vector<double>>& g) {
    vector<vector<double>> dp(m + 1, vector<double>(n, -1));
    for (int i = 0; i < n; ++i) {
        dp[1][i] = 1.0;
    }

    for (int i = 2; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                dp[i][j] = max(dp[i][j], dp[i - 1][k] * g[k][j]);
            }
        }
    }

    double ans = -1;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp[m][i]);
    }
    return ans;
}

vector<vector<double>> generateInput(int n) {
    vector<vector<double>> g(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }
    return g;
}