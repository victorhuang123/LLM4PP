#pragma once

#include <algorithm>
#include <vector>

using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define INF (1<<28)

int baseline(int n, int m, const vector<int>& a, const vector<int>& b, const vector<int>& c) {
    vector<vector<vector<int>>> dp(64, vector<vector<int>>(64, vector<int>(64, -INF)));
    dp[0][0][0] = 0;

    rep (k, n) rep (x, m+1) rep (i, x+1) if (dp[k][x][i] > -INF) {
        rep (j, m-x+1) {
            int ans = c[k];
            rep (ii, j+1) rep (jj, i+1) if (1 <= ii+jj && ii+jj <= 8) {
                ans = max(ans, a[k]*ii + b[k]*jj);
            }
            dp[k+1][x+j][j] = max(dp[k+1][x+j][j], dp[k][x][i] + ans);
        }
    }

    int ans = -INF;
    rep (x, m+1) rep (i, 64) ans = max(ans, dp[n][x][i]);
    return ans;
}

vector<int> generateInput(int n) {
    vector<int> input(n);
    for (int i = 0; i < n; ++i) {
        input[i] = i + 1;
    }
    return input;
}