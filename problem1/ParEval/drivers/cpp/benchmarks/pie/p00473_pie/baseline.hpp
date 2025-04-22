#pragma once

#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

#define INF 2000000000

int baseline(int n, const vector<int>& a) {
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(n + 1, vector<int>(2, INF)));
    dp[0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[0][j][0] < INF) {
                dp[1][j + 1][0] = min(dp[1][j + 1][0], dp[0][j][0]);
                dp[1][j + 1][1] = min(dp[1][j + 1][1], dp[0][j][0] + a[i + 1]);
            }
            if (dp[0][j][1] < INF) {
                dp[1][j][1] = min(dp[1][j][1], dp[0][j][1]);
                dp[1][j][0] = min(dp[1][j][0], dp[0][j][1] + a[i + 1]);
            }
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j][0] = dp[1][j][0];
            dp[0][j][1] = dp[1][j][1];
            dp[1][j][0] = INF;
            dp[1][j][1] = INF;
        }
    }

    return min(dp[0][n / 2][0], dp[0][n / 2][1]);
}

vector<int> generateInput(int n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}