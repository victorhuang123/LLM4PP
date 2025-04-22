#pragma once

#include <algorithm>
#include <vector>

long long int baseline(long long int a, long long int b) {
    long long int m = std::max(a, b);
    long long int mn = std::min(a, b);
    for (long long int i = 1; i <= mn; i++) {
        if ((m * i) % mn == 0) {
            return m * i;
        }
    }
    return -1; // This line is theoretically unreachable as LCM always exists for positive integers.
}

std::vector<long long int> generateInput() {
    return {123456789012345678, 987654321098765432};
}