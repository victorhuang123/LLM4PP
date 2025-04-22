#pragma once

#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int dp[64][64][64];

int dfs(int c, int a, int n) {
    if (dp[c][a][n] >= 0) return dp[c][a][n];
    int res = 0;
    if (c > 0 && a > 0 && n > 0) res = max(res, dfs(c - 1, a - 1, n - 1) + 1);
    if (c > 1 && a > 0) res = max(res, dfs(c - 2, a - 1, n) + 1);
    if (c > 2) res = max(res, dfs(c - 3, a, n) + 1);
    return dp[c][a][n] = res;
}

int baseline(int c, int a, int n) {
    memset(dp, -1, sizeof(dp));
    int res = 0;
    while (c > 8 && a > 4 && n > 0) {
        res++;
        c--;
        a--;
        n--;
    }

    while (c > 8 && a > 4) {
        res++;
        c -= 2;
        a--;
    }

    while (c > 8) {
        res++;
        c -= 3;
    }
    res += dfs(c, a, n);
    return res;
}

vector<int> generateInput() {
    return {100, 100, 100};
}