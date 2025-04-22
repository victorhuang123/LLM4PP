#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int baseline(int n, int m, int num, const vector<int>& a, const vector<vector<int>>& costl, const vector<vector<int>>& costs) {
    vector<vector<int>> dp(num + 1, vector<int>(n + 1, INT_MAX / 3));
    dp[1][a[0]] = 0;

    for (int i = 2; i <= num; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + costl[a[i - 2]][a[i - 1]]);
            for (int k = 1; k <= n; ++k) {
                dp[i][j] = min(dp[i][j], dp[i - 1][k] + costl[a[i - 2]][k] + costs[k][j] + costl[j][a[i - 1]]);
            }
        }
    }

    int ans = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        ans = min(ans, dp[num][i]);
    }
    return ans;
}

vector<vector<int>> generateInput(int n, int m) {
    vector<vector<int>> costl(n + 1, vector<int>(n + 1, INT_MAX / 3));
    vector<vector<int>> costs(n + 1, vector<int>(n + 1, INT_MAX / 3));

    for (int i = 1; i <= n; ++i) {
        costl[i][i] = costs[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        int val = rand() % 1000 + 1;
        if (rand() % 2 == 0) {
            costl[x][y] = costl[y][x] = min(val, costl[x][y]);
        } else {
            costs[x][y] = costs[y][x] = min(val, costs[x][y]);
        }
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                costs[i][j] = min(costs[i][j], costs[i][k] + costs[k][j]);
                costl[i][j] = min(costl[i][j], costl[i][k] + costl[k][j]);
            }
        }
    }

    return {costl, costs};
}