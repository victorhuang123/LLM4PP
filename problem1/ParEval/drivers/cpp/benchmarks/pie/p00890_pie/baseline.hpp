#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int baseline(int N, int M, int C, vector<int>& u, vector<int>& v, vector<int>& w) {
    vector<vector<int>> g(N, vector<int>(N, -1));
    vector<vector<int>> dp(M + 1, vector<int>(N, -1));

    for (int i = 0; i < N; i++) g[i][i] = 0;
    for (int i = 0; i < M; i++) {
        u[i]--, v[i]--;
        g[u[i]][v[i]] = w[i];
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            if (g[i][k] != -1) {
                for (int j = 0; j < N; j++) {
                    if (g[k][j] != -1) {
                        if (g[i][j] == -1 || g[i][j] > g[i][k] + g[k][j]) {
                            g[i][j] = g[i][k] + g[k][j];
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; i++) dp[0][i] = g[0][i];

    for (int k = 0; k <= M; k++) {
        if (dp[k][N - 1] <= C) {
            return k;
        }
        for (int i = 0; i < M; i++) {
            if (dp[k][u[i]] != -1) {
                for (int j = 0; j < N; j++) {
                    if (g[v[i]][j] != -1) {
                        if (dp[k + 1][j] == -1 || dp[k + 1][j] > dp[k][u[i]] + g[v[i]][j]) {
                            dp[k + 1][j] = dp[k][u[i]] + g[v[i]][j];
                        }
                    }
                }
            }
        }
    }

    return -1;
}

vector<int> generateInput(int N, int M, int C) {
    vector<int> u(M), v(M), w(M);
    for (int i = 0; i < M; i++) {
        u[i] = rand() % N + 1;
        v[i] = rand() % N + 1;
        w[i] = rand() % 100 + 1;
    }
    return {N, M, C, u, v, w};
}