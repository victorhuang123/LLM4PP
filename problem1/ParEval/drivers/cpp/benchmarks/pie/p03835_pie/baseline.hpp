#pragma once

#include <vector>
#include <functional>

int baseline(int n, int m) {
    std::vector<std::vector<int>> dp(5, std::vector<int>(10010, -1));

    std::function<int(int, int)> dfs = [&](int now, int sy) {
        if (now > 3) return !sy;
        if (dp[now][sy] != -1) return dp[now][sy];
        int res = 0;
        for (int i = 0; i <= std::min(n, sy); i++) {
            res += dfs(now + 1, sy - i);
        }
        return dp[now][sy] = res;
    };

    return dfs(1, m);
}