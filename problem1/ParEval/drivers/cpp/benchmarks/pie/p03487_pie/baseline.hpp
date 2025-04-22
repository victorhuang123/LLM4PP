#pragma once

#include <vector>
#include <algorithm>

long long baseline(long long n, const std::vector<int>& input) {
    std::vector<int> c(100001, 0);
    long long count = 0;

    for (long long i = 0; i < n; ++i) {
        int x = input[i];
        if (x >= 100001) {
            count++;
            continue;
        }
        c[x]++;
    }

    for (int i = 1; i < 100001; ++i) {
        count += (c[i] < i) ? c[i] : c[i] - i;
    }

    return count;
}

std::vector<int> generateInput(long long n) {
    std::vector<int> input(n);
    for (long long i = 0; i < n; ++i) {
        input[i] = i % 100002; // Ensure some values are >= 100001
    }
    return input;
}