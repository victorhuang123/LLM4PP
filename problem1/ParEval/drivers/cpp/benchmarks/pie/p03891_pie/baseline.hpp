#pragma once

#include <vector>

std::vector<std::vector<int>> baseline(int a[3][3]) {
    int x = a[1][1] * 3;
    a[0][2] = x - a[0][0] - a[0][1];
    a[2][1] = x - a[0][1] - a[1][1];
    a[2][2] = x - a[0][0] - a[1][1];
    a[2][0] = x - a[1][1] - a[0][2];
    a[1][0] = x - a[0][0] - a[2][0];
    a[1][2] = x - a[0][2] - a[2][2];

    std::vector<std::vector<int>> result(3, std::vector<int>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = a[i][j];
        }
    }
    return result;
}