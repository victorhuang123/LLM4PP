#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int n, int k, vector<int>& a) {
    vector<vector<bool>> dp1(n + 1, vector<bool>(k + 1, false));
    vector<vector<bool>> dp2(n + 1, vector<bool>(k + 1, false));

    dp1[0][0] = true;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            if (dp1[i][j]) dp1[i + 1][j] = true;
            if (j + a[i] <= k) dp1[i + 1][j + a[i]] = dp1[i + 1][j + a[i]] || dp1[i][j];
        }
    }

    dp2[0][0] = true;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            if (dp2[i][j]) dp2[i + 1][j] = true;
            if (j + a[n - 1 - i] <= k) dp2[i + 1][j + a[n - 1 - i]] = dp2[i + 1][j + a[n - 1 - i]] || dp2[i][j];
        }
    }

    int need = 0;

    for (int i = 1; i <= n; ++i) {
        int target = max(0, k - a[i - 1]);
        for (int j = target; j <= k - 1; ++j) {
            for (int l = 0; l <= j; ++l) {
                if (dp1[i - 1][l] && dp2[n - i][j - l]) {
                    ++need;
                    j = l = k + 5;
                }
            }
        }
    }

    return n - need;
}

vector<int> generateInput(int n) {
    return vector<int>(n, 1);
}