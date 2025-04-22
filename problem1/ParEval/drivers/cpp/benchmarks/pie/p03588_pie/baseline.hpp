#pragma once

#include <vector>
#include <algorithm>
#include <climits>

int baseline(int n, const std::vector<int>& a, const std::vector<int>& b) {
    int ans = 0, ma = 0, mi = INT_MAX;
    for (int i = 0; i < n; i++) {
        mi = std::min(b[i], mi);
        if (mi == b[i]) ma = a[i];
    }
    return ma + mi;
}

std::vector<std::pair<std::vector<int>, std::vector<int>>> generate_input() {
    int n = 100000;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = n - i;
    }
    return {{a, b}};
}