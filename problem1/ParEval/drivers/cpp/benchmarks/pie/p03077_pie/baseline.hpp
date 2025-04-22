#pragma once

#include <vector>
#include <cstdint>

int64_t baseline(int64_t N, const std::vector<int64_t>& a) {
    int64_t mn = 1000000000000000;

    for (int64_t i = 0; i < 5; ++i) {
        if (a[i] < mn) {
            mn = a[i];
        }
    }
    return (N + mn - 1) / mn + 4;
}

std::vector<int64_t> generateInput() {
    return {1, 2, 3, 4, 5};
}