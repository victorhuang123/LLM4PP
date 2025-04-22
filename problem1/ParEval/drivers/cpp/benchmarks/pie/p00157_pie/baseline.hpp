#pragma once

#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> P;

int baseline(int n, int m, vector<P>& mt) {
    vector<vector<int>> dp(1000, vector<int>(201, 1000)); // dp[h][k] stores the minimum radius for k layers at height h

    // Sort materials by height
    sort(mt.begin(), mt.end());

    // Fill the dp table
    for (int i = 0; i < m + n; i++) {
        int h = mt[i].first;
        int r = mt[i].second;
        dp[h][1] = min(dp[h][1], r);

        for (int j = 0; j < h; j++) {
            for (int k = 0; k < m + n; k++) {
                if (r > dp[j][k]) {
                    dp[h][k + 1] = min(dp[h][k + 1], r);
                }
            }
        }
    }

    // Find the maximum number of layers
    int ans = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j <= m + n; j++) {
            if (dp[i][j] != 1000) {
                ans = max(ans, j);
            }
        }
    }

    return ans;
}

vector<P> generateInput(int n, int m) {
    vector<P> mt;
    for (int i = 1; i <= n + m; i++) {
        mt.push_back({i, i + 1});
    }
    return mt;
}