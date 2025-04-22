#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double baseline(int n, int m, int k) {
    const int s = n * m;
    vector<vector<double>> dp(n + 1, vector<double>(s + 1, 0.0));

    dp[0][0] = 1.0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= s; ++j) {
            double p = dp[i][j] / m;
            for (int nj = j + 1, u = min(j + m, s); nj <= u; ++nj) {
                dp[i + 1][nj] += p;
            }
        }
    }

    double res = 0.0;
    for (int j = 0; j <= s; ++j) {
        res += max(1, j - k) * dp[n][j];
    }
    return res;
}

vector<int> generateInput() {
    return {40, 10000, 10000};
}