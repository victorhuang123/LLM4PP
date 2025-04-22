#pragma once

#include <vector>

int baseline(int n, int m, const std::vector<std::vector<int>>& a) {
    int ans = 0;

    auto dfs = [&](int x, auto&& dfs) -> void {
        if (x >= n) return;
        else {
            int sum = 0;
            for (int i = 0; i < m; i++) {
                int count = 0;
                for (int j = 0; j < n; j++) {
                    if (a[j][i] == 1) count++;
                }
                sum += std::max(count, n - count);
            }
            if (sum > ans) ans = sum;
            dfs(x + 1, dfs);
            for (int i = 0; i < m; i++) {
                a[x][i] = 1 - a[x][i];
            }
            dfs(x + 1, dfs);
            for (int i = 0; i < m; i++) {
                a[x][i] = 1 - a[x][i];
            }
        }
    };
    dfs(0, dfs);
    return ans;
}

std::vector<std::vector<int>> generateInput(int n, int m) {
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = (i + j) % 2;
        }
    }
    return a;
}