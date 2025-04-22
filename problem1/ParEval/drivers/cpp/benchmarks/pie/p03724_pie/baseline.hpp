#pragma once

#include<vector>
#include<algorithm>

std::vector<int> generateInput(int n, int m) {
    std::vector<int> b(m), c(m);
    for (int i = 0; i < m; ++i) {
        b[i] = i % n;
        c[i] = (i + 1) % n;
    }
    return {b, c};
}

bool baseline(int n, int m, const std::vector<int>& b, const std::vector<int>& c) {
    std::vector<int> a(n, 0);
    for (int i = 0; i < m; ++i) {
        a[b[i]]++;
        a[c[i]]++;
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] % 2 != 0)
            return false;
    }
    return true;
}