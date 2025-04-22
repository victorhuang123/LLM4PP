#pragma once

#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

inline int f(int n) {
    return max(0, min(255, n));
}

int baseline(int N, int M, const vector<int>& cs, const vector<int>& xs) {
    vector<vector<int>> dp(N + 1, vector<int>(256, 100000000));
    dp[0][128] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= 255; j++) {
            for (int k = 0; k < M; k++) {
                const int y = f(j + cs[k]);
                dp[i + 1][y] = min(dp[i + 1][y], dp[i][j] + (xs[i] - y) * (xs[i] - y));
            }
        }
    }

    int ans = numeric_limits<int>::max();
    for (int i = 0; i <= 255; i++) {
        ans = min(ans, dp[N][i]);
    }

    return ans;
}

vector<int> generateInput(int N, int M) {
    vector<int> cs(M);
    vector<int> xs(N);

    for (int i = 0; i < M; i++) {
        cs[i] = rand() % 256;
    }

    for (int i = 0; i < N; i++) {
        xs[i] = rand() % 256;
    }

    return {N, M, cs, xs};
}