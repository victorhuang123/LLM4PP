#pragma once

#include <vector>
#include <algorithm>

int baseline(long long x, long long y) {
    int nr = 1;
    while (x * 2 <= y) {
        nr++;
        x *= 2;
    }
    return nr;
}

std::vector<std::pair<long long, long long>> generateInput() {
    std::vector<std::pair<long long, long long>> inputs;
    inputs.push_back({1, 1000000000000000000LL});
    return inputs;
}