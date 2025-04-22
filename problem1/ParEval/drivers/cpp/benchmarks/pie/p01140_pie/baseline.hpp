#pragma once

#include <vector>

std::vector<int> generateInput() {
    std::vector<int> h(1501, 0);
    std::vector<int> w(1501, 0);
    for (int i = 1; i < 1501; ++i) {
        h[i] = h[i-1] + i;
        w[i] = w[i-1] + i;
    }
    return h;
}

int baseline(const std::vector<int>& h, const std::vector<int>& w) {
    std::vector<int> dat(1500001, 0);
    int n = h.size();
    int m = w.size();

    for (int i = 0; i < m - 1; ++i) {
        for (int j = i + 1; j < m; ++j) {
            dat[w[j] - w[i]]++;
        }
    }

    int cnt = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            cnt += dat[h[j] - h[i]];
        }
    }

    return cnt;
}