
#include <vector>
#include <algorithm>
#include <climits>

int baseline(int n, int m, std::vector<int>& w, std::vector<int>& v) {
    std::vector<std::vector<std::vector<int>>> dp(n + 1, std::vector<std::vector<int>>(n + 1, std::vector<int>(301, INT_MIN)));
    dp[0][0][0] = 0;
    int ans = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= 300; ++k) {
                if (1LL * j * w[0] + k > 1LL * m) continue;
                if (j + 1 <= n && k + w[i + 1] - w[0] >= 0 && k + w[i + 1] - w[0] <= 300) {
                    dp[i + 1][j + 1][k + w[i + 1] - w[0]] = std::max(dp[i + 1][j + 1][k + w[i + 1] - w[0]], dp[i][j][k] + v[i + 1]);
                }
                dp[i + 1][j][k] = std::max(dp[i + 1][j][k], dp[i][j][k]);
            }
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= 300; ++j) {
            if (1LL * i * w[0] + j > 1LL * m) continue;
            ans = std::max(ans, dp[n][i][j]);
        }
    }

    return ans;
}

