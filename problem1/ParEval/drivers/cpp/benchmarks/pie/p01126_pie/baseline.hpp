#pragma once

#include <vector>

int baseline(int n, int m, int a, std::vector<std::vector<int>>& y) {
    for (int i = 1000; i > 0; i--) {
        if (y[i][a] != 0) a = y[i][a];
    }
    return a;
}

std::vector<std::vector<int>> generateInput() {
    int n = 1000;
    int m = 1000;
    std::vector<std::vector<int>> y(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            y[i][j] = (i + j) % m + 1;
        }
    }
    return y;
}