#pragma once

#include <vector>
#include <cmath>

long baseline(long n) {
    for (long i = n; ; i--) {
        if (floor(sqrt(i)) * floor(sqrt(i)) == i) {
            return i;
        }
    }
}

std::vector<long> generateInput() {
    return {1000000000000}; // Example input to maximize the problem scale
}