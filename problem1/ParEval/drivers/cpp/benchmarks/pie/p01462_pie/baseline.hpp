
#include <vector>
#include <cmath>
using namespace std;



double baseline(int n, int m, int p, vector<vector<int>>& e) {
    vector<int> num(1 << n);
    vector<double> dp(1 << n, 0.0);

    for (int i = 1; i <= m; ++i) {
        int u = e[i][0];
        int v = e[i][1];
        for (int j = 1; j < (1 << n); ++j) {
            if ((j & (1 << (u - 1))) && (j & (1 << (v - 1)))) {
                num[j]++;
            }
        }
    }

    for (int i = 1; i < (1 << n); ++i) {
        for (int j = i & (i - 1); j; j = i & (j - 1)) {
            if (j & (i & (-i))) {
                double q = pow(p / 100.0, num[i] - num[j] - num[i & (~j)]);
                dp[i] += (1 - dp[j]) * q;
            }
        }
    }

    return 1 - dp[(1 << n) - 1];
}