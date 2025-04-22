#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int baseline(int lim, int N, int M, int X, const vector<int>& sx, const vector<int>& sy, const vector<int>& x, const vector<int>& y) {
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(1001, vector<int>(101, INT_MIN)));

    dp[0][0][0] = 0;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j <= lim; j++) {
            for (int k = 0; k <= M; k++) {
                dp[(i & 1) ^ 1][j][k] = dp[i & 1][j][k];
            }
        }
        for (int j = 0; j + x[i] <= lim; j++) {
            for (int k = 0; k < M; k++) {
                dp[(i & 1) ^ 1][j + x[i]][k + 1] = max(dp[(i & 1) ^ 1][j + x[i]][k + 1], dp[i & 1][j][k] + y[i]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            int rem = lim - sx[i] - sx[j];
            for (int w = 0; w <= rem; w++) {
                for (int z = X; z <= M; z++) {
                    ans = max(ans, sy[i] + sy[j] + dp[M & 1][w][z]);
                }
            }
        }

    for (int i = 0; i < N; i++) {
        int rem = lim - sx[i];
        for (int w = 0; w <= rem; w++) {
            for (int z = X; z <= M; z++) {
                ans = max(ans, sy[i] + dp[M & 1][w][z]);
            }
        }
    }

    return ans;
}

vector<int> generateInput(int N, int M) {
    vector<int> sx(N), sy(N), x(M), y(M);
    for (int i = 0; i < N; i++) {
        sx[i] = rand() % 100 + 1;
        sy[i] = rand() % 100 + 1;
    }
    for (int i = 0; i < M; i++) {
        x[i] = rand() % 100 + 1;
        y[i] = rand() % 100 + 1;
    }
    return {sx, sy, x, y};
}