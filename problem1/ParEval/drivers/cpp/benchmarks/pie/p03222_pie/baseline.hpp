#pragma once

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int baseline(int H, int W, int K) {
    vector<vector<int>> dp(H + 1, vector<int>(W, 0));
    dp[0][0] = 1;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            for (int bit = 0; bit < 1 << (W - 1); bit++) {
                bool ok = true;
                for (int k = 0; k < W - 2; k++) {
                    if (bit & (1 << k) && bit & (1 << (k + 1))) {
                        ok = false;
                    }
                }
                if (!ok) continue;

                if (0 < j && (bit & (1 << (j - 1)))) {
                    dp[i + 1][j - 1] += dp[i][j];
                    dp[i + 1][j - 1] %= mod;
                } else if (j < W - 1 && (bit & (1 << j))) {
                    dp[i + 1][j + 1] += dp[i][j];
                    dp[i + 1][j + 1] %= mod;
                } else {
                    dp[i + 1][j] += dp[i][j];
                    dp[i + 1][j] %= mod;
                }
            }
        }
    }

    return dp[H][K - 1];
}

vector<int> generateInput() {
    int H = 100;
    int W = 20;
    int K = 10;
    return {H, W, K};
}