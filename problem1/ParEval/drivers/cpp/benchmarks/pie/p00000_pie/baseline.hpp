#pragma once

#include <vector>

std::vector<std::vector<int>> baseline(int n) {
    std::vector<std::vector<int>> result(n, std::vector<int>(n));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            result[i-1][j-1] = i * j;
        }
    }
    return result;
}

std::vector<std::vector<int>> generateInput(int n) {
    return std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
}