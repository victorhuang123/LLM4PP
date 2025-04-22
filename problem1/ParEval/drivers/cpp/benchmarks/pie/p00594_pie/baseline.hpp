#pragma once

#include <vector>
#include <algorithm>

int baseline(int n, const std::vector<int>& t) {
    std::vector<int> sorted_t = t;
    std::sort(sorted_t.begin(), sorted_t.end());
    int key = sorted_t[0];
    int cnt = 1;
    int ans = -1;

    for (int i = 1; i <= n; i++) {
        if (i < n && key == sorted_t[i]) {
            cnt++;
        } else {
            if (cnt > n / 2) {
                ans = key;
                break;
            }
            if (i < n) {
                key = sorted_t[i];
                cnt = 1;
            }
        }
    }

    return ans;
}

std::vector<int> generateInput(int n) {
    std::vector<int> t(n);
    for (int i = 0; i < n / 2 + 1; i++) {
        t[i] = 1;
    }
    for (int i = n / 2 + 1; i < n; i++) {
        t[i] = 2;
    }
    return t;
}