#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int H, int W, const vector<vector<int>>& A) {
    vector<vector<int>> dp(W, vector<int>(W, -1e9));
    dp[0][1] = 0;

    for (int _ = 0; _ < H; _++) {
        for (int i = 0; i < W; i++) {
            for (int j = i + 1; j < W; j++) {
                dp[i][j] += A[_][i];
                if (i + 1 < j) dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            }
        }

        for (int i = 0; i < W; i++) {
            for (int j = i + 1; j < W; j++) {
                dp[i][j] += A[_][j];
                if (j + 1 < W) dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i + 1 < W; i++) ans = max(ans, dp[i][W - 1]);
    return ans;
}

vector<vector<int>> generateInput(int H, int W) {
    vector<vector<int>> A(H, vector<int>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            A[i][j] = rand() % 100;
        }
    }
    return A;
}