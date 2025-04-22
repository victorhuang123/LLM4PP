#pragma once

#include<vector>

int baseline(int a, int b) {
    for (int i = 0; i <= 1114514; i++) {
        int m = i * 0.08;
        int n = i * 0.1;
        if (m == a && n == b) {
            return i;
        }
    }
    return -1;
}

std::vector<int> generateInput() {
    return {1114514, 1114514};
}