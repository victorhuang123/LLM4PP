#pragma once

#include <vector>
#include <algorithm>
#include <cstring>

typedef long double ld;

ld baseline(int n, int c, const std::vector<int>& a) {
    ld dp[555][555];
    ld fac = 0, pwd = 1;

    for (int i = 1; i < n; i++) pwd *= c;
    std::vector<int> sorted_a = a;
    std::sort(sorted_a.begin() + 1, sorted_a.end());

    ld ans = 0;
    do {
        memset(dp, 0, sizeof(dp));
        fac++;
        dp[sorted_a[n] * n][0] = 1;

        for (int i = 1; i <= n * c; i++) {
            int v = i % n;
            if (!v) continue;
            for (int ii = i; ii <= n * c; ii++) {
                for (int S = 0; S < (1 << (n - 1)); S++) {
                    if (S & (1 << (v - 1))) continue;
                    int to = min(n * c, max(ii, i + n * sorted_a[v]));
                    dp[to][S | (1 << (v - 1))] += dp[ii][S];
                }
            }
        }
        ans += dp[n * c][(1 << (n - 1)) - 1] / pwd;
    } while (std::next_permutation(sorted_a.begin() + 1, sorted_a.end()));

    return ans / fac;
}

std::vector<int> generateInput(int n) {
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
    return a;
}