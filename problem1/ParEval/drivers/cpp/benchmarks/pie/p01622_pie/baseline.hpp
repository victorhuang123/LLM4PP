#pragma once

#include <vector>
#include <algorithm>

int baseline(int n, const std::vector<int>& r, const std::vector<int>& w) {
    int sum_r = 0, sum_w = 0, idx = 0;
    std::vector<std::vector<bool>> dp(1001, std::vector<bool>(1000, false));

    for (int i = 0; i < n; i++) {
        sum_r += r[i];
        sum_w += w[i];
        if (r[idx] < r[i]) idx = i;
    }

    int r0 = r[idx], r_sum = sum_r - r0;
    std::vector<int> modified_w = w;
    modified_w[idx] = 0;

    if (r0 <= r_sum) {
        return sum_r + sum_w;
    } else {
        int res = 2 * r0;

        dp[0][0] = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 1000; j++) {
                if (dp[i][j]) {
                    dp[i + 1][j] = true;
                    if (j + modified_w[i] < 1000)
                        dp[i + 1][j + modified_w[i]] = true;
                }
            }
        }

        int opt = r0 - r_sum;
        while (!dp[n][opt]) opt--;

        res += sum_w - opt;
        return res;
    }
}

std::pair<std::vector<int>, std::vector<int>> generateInput(int n) {
    std::vector<int> r(n), w(n);
    for (int i = 0; i < n; i++) {
        r[i] = rand() % 1000 + 1;
        w[i] = rand() % 1000 + 1;
    }
    return {r, w};
}