#pragma once

#include <vector>

std::pair<long long, long long> baseline(const std::vector<int>& A) {
    int n = A.size();
    long long min = 2, max = 2;

    for (int i = n - 1; i >= 0; i--) {
        max = A[i] * (max / A[i]);
        max = max + A[i] - 1;
        min = A[i] * ((min - 1) / A[i] + 1);

        if (max < min) {
            return {-1, -1};
        }
    }

    return {min, max};
}

std::vector<int> generateInput() {
    return std::vector<int>(100000, 2); // Example input with 100000 elements, all set to 2
}