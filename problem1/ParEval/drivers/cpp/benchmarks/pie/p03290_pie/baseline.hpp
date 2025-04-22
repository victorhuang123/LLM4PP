#pragma once

#include <algorithm>
#include <vector>
#include <climits>

const int MOD = 1e9+7;

int baseline(int d, int g, std::vector<int>& p, std::vector<int>& c) {
    g /= 100;
    std::vector<std::vector<int>> dp(200000, std::vector<int>(11, MOD));

    for (int i = 1; i <= d; i++) {
        c[i-1] /= 100;
    }
    dp[0][0] = 0;

    for (int i = 0; i <= g; i++) {
        for (int j = 1; j <= d; j++) {
            if (dp[i][j-1] != MOD) {
                for (int k = 0; k < p[j-1]; k++) {
                    dp[i+j*k][j] = std::min(dp[i][j-1] + k, dp[i+j*k][j]);
                }
                dp[i+j*p[j-1]+c[j-1]][j] = std::min(dp[i][j-1] + p[j-1], dp[i+j*p[j-1]+c[j-1]][j]);
            }
        }
    }

    int ans = MOD;
    for (int i = g; i <= g+20000; i++) {
        for (int j = 1; j <= d; j++) {
            ans = std::min(ans, dp[i][j]);
        }
    }
    return ans;
}

std::vector<int> generateInput(int d, int g, std::vector<int>& p, std::vector<int>& c) {
    std::vector<int> input;
    input.push_back(d);
    input.push_back(g);
    input.insert(input.end(), p.begin(), p.end());
    input.insert(input.end(), c.begin(), c.end());
    return input;
}