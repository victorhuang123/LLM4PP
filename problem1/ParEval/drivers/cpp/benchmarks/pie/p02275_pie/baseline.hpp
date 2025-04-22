#pragma once

#include <vector>
#include <algorithm>

std::vector<int> baseline(const std::vector<int>& arr) {
    int n = arr.size();
    std::vector<int> c(100001, 0);
    std::vector<int> ans(n);

    for (int i = 0; i < n; ++i) {
        ++c[arr[i]];
    }

    for (int i = 1; i < 100001; ++i) {
        c[i] += c[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        ans[c[arr[i]] - 1] = arr[i];
        --c[arr[i]];
    }

    return ans;
}

std::vector<int> generateInput() {
    int n = 2000000;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100000 + 1;
    }
    return arr;
}