#pragma once

#include <vector>

int baseline(int n, int m, const std::vector<std::vector<int>>& ice) {
    std::vector<std::vector<int>> masu(n + 2, std::vector<int>(m + 2, 0));
    int mx = 0;

    auto func = [&](int x, int y, int now, auto&& func) -> void {
        if (masu[x + 1][y] == 1) {
            masu[x][y] = 0;
            func(x + 1, y, now + 1, func);
            masu[x][y] = 1;
        }
        if (masu[x - 1][y] == 1) {
            masu[x][y] = 0;
            func(x - 1, y, now + 1, func);
            masu[x][y] = 1;
        }
        if (masu[x][y + 1] == 1) {
            masu[x][y] = 0;
            func(x, y + 1, now + 1, func);
            masu[x][y] = 1;
        }
        if (masu[x][y - 1] == 1) {
            masu[x][y] = 0;
            func(x, y - 1, now + 1, func);
            masu[x][y] = 1;
        } else {
            if (mx < now) {
                mx = now;
            }
        }
    };

    auto func2 = [&]() -> void {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                masu[i][j] = ice[i - 1][j - 1];
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            func2();
            if (masu[i][j] == 1) {
                func(i, j, 1, func);
            }
        }
    }

    return mx;
}

std::vector<std::vector<int>> generateInput(int n, int m) {
    std::vector<std::vector<int>> ice(n, std::vector<int>(m, 1));
    return ice;
}