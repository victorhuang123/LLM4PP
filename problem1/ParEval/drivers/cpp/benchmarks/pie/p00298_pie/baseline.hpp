
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>

using namespace std;

long long baseline(int n, const vector<long long>& c, const vector<long long>& w) {
    vector<long long> sum(n + 1, 0);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));

    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + w[i - 1];
    }

    auto getsum = [&](int l, int r) {
        return sum[r] - sum[l];
    };

    for (int i = 0; i <= n; ++i) {
        dp[i][i + 1] = 1;
    }

    for (int wid = 2; wid <= n; ++wid) {
        for (int l = 0; l <= n - wid; ++l) {
            int r = l + wid;

            for (int mid = l + 1; mid < r; ++mid) {
                dp[l][r] = min(dp[l][r], dp[l][mid] + dp[mid][r]);
            }

            long long w_s = getsum(l + 1, r);
            if (c[l] >= w_s && dp[l + 1][r] == 1) {
                dp[l][r] = 1;
            }

            w_s = getsum(l, r - 1);
            if (c[r - 1] >= w_s && dp[l][r - 1] == 1) {
                dp[l][r] = 1;
            }
        }
    }

    return dp[0][n];
}

