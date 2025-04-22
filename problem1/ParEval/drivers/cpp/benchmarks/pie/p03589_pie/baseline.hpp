#pragma once

#include <vector>

std::vector<long long> baseline(long long N) {
    long long h, n, w;
    long long up, down;
    std::vector<long long> result;

    w = 0;
    for (h = 1; h <= 3500; h++) {
        for (n = 1; n <= 3500; n++) {
            up = 4 * h * n - N * h - N * n;
            down = N * h * n;
            if (up > 0 && down % up == 0 && down / up <= 3500) {
                w = down / up;
                result = {h, n, w};
                return result;
            }
            if (w != 0) {
                break;
            }
        }
        if (w != 0) {
            break;
        }
    }
    return result;
}

std::vector<long long> generateInput() {
    return {3500};
}