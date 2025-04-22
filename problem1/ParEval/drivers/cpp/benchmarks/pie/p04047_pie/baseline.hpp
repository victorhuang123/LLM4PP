#pragma once

#include <algorithm>
#include <vector>

long long baseline(int n, const std::vector<long long>& a) {
    std::vector<long long> sorted_a = a;
    std::sort(sorted_a.begin(), sorted_a.end());
    long long sum = 0;
    for (int i = 0; i < 2 * n; i += 2) {
        sum += sorted_a[i];
    }
    return sum;
}

std::vector<long long> generate_input(int n) {
    std::vector<long long> a(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        a[i] = rand() % 1000000;
    }
    return a;
}