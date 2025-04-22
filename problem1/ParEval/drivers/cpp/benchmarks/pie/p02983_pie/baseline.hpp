#pragma once

#include <vector>
#include <algorithm>

int baseline(long l, long r) {
    int min = 2018;
    if (abs(l - r) > 2019) {
        return 0;
    } else {
        l = l % 2019;
        r = r % 2019;
        for (int i = l; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                if (i * j % 2019 < min) {
                    min = i * j % 2019;
                }
            }
        }
        return min;
    }
}

std::pair<long, long> generateInput() {
    return {0, 2019};
}