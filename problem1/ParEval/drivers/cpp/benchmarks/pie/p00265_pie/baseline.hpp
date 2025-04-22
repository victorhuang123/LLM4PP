#pragma once

#include <vector>
#include <algorithm>
#define C 300000

std::vector<int> generateInput(int n, int q) {
    std::vector<int> c(n);
    std::vector<int> query(q);
    for (int i = 0; i < n; i++) {
        c[i] = rand() % (C + 1);
    }
    for (int i = 0; i < q; i++) {
        query[i] = rand() % (C + 1) + 1;
    }
    return c;
}

std::vector<int> baseline(int n, int q, const std::vector<int>& c, const std::vector<int>& query) {
    std::vector<bool> has_c(C + 1, false);
    for (int i = 0; i < n; i++) {
        has_c[c[i]] = true;
    }
    std::vector<int> result(q);
    for (int i = 0; i < q; i++) {
        int max_r = -1;
        for (int r = query[i] - 1; r >= 0; r--) {
            for (int k = 0; true; k++) {
                int x = k * query[i] + r;
                if (x > C) {
                    break;
                }
                if (has_c[x]) {
                    max_r = std::max(r, max_r);
                    break;
                }
            }
            if (max_r >= 0) {
                break;
            }
        }
        result[i] = max_r;
    }
    return result;
}