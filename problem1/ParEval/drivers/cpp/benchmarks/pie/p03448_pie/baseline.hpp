#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int a1, int a2, int a3, int x) {
    vector<int> a = {0, a1, a2, a3};
    vector<int> c = {0, 500, 100, 50};
    vector<vector<int>> dp(4, vector<int>(x + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= 3; i++) {
        for (int j = 0; j <= x; j++) {
            int num = j / c[i];
            num = min(num, a[i]);
            for (int k = 0; k <= num; k++) {
                dp[i][j] += dp[i - 1][j - k * c[i]];
            }
        }
    }

    return dp[3][x];
}

vector<int> generateInput() {
    return {1000, 1000, 1000, 100000};
}