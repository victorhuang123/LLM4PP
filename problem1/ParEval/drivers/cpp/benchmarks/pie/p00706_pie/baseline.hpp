#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int N, int W, int H, int S, int T, vector<int>& X, vector<int>& Y) {
    vector<vector<int>> dp(H + 1, vector<int>(W + 1, 0));
    vector<vector<bool>> field(H + 1, vector<bool>(W + 1, false));

    for (int i = 0; i < N; i++) {
        field[Y[i]][X[i]] = true;
    }

    for (int x = 1; x <= W; x++) {
        for (int y = 1; y <= H; y++) {
            dp[y][x] = dp[y - 1][x] + dp[y][x - 1] - dp[y - 1][x - 1] + field[y][x];
        }
    }

    int res = 0;
    for (int x = S; x <= W; x++) {
        for (int y = T; y <= H; y++) {
            res = max(res, dp[y][x] - dp[y - T][x] - dp[y][x - S] + dp[y - T][x - S]);
        }
    }

    return res;
}

vector<int> generateX(int N, int W) {
    vector<int> X(N);
    for (int i = 0; i < N; i++) {
        X[i] = (i % W) + 1;
    }
    return X;
}

vector<int> generateY(int N, int H) {
    vector<int> Y(N);
    for (int i = 0; i < N; i++) {
        Y[i] = (i / H) + 1;
    }
    return Y;
}