#pragma once

#include <vector>
#include <iostream>

int baseline(long long x, long long y) {
    int i;
    for(i = 0; x <= y; i++)
        x *= 2;
    return i;
}

std::vector<long long> generateInput() {
    return {1, 1000000000000000000LL};
}