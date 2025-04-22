#pragma once

#include <vector>
#include <algorithm>

int baseline(int n, int k, int m) {
    std::vector<int> b(n + 1, 0);
    auto add = [&](int idx, int val) {
        while (idx <= n) {
            b[idx] += val;
            idx += idx & -idx;
        }
    };
    auto sum = [&](int idx) {
        int res = 0;
        while (idx > 0) {
            res += b[idx];
            idx -= idx & -idx;
        }
        return res;
    };
    auto lower_bound = [&](int x) {
        int idx = 0;
        for (int i = 20; i >= 0; i--) {
            if (idx + (1 << i) <= n && b[idx + (1 << i)] < x) {
                idx += 1 << i;
                x -= b[idx];
            }
        }
        return idx + 1;
    };

    for (int i = 1; i <= n; i++) add(i, 1);
    for (n--; n > 0; n--) {
        add(m, -1);
        int x = (sum(m) + k) % n;
        if (x == 0) x = n;
        m = lower_bound(x);
    }
    return m;
}

std::vector<int> generateInput() {
    int n = 1000000;  // Large input size to test efficiency
    int k = 123456;
    int m = 654321;
    return {n, k, m};
}