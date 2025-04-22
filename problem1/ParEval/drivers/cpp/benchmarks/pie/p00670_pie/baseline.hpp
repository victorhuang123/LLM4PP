#pragma once

#include <vector>
#include <algorithm>

int baseline(int n, int S, const std::vector<int>& r) {
    std::vector<int> sorted_r = r;
    std::sort(sorted_r.begin(), sorted_r.end());
    int res = 0;
    for(int i=0; i+1<n; i++) {
        auto it = std::upper_bound(sorted_r.begin()+i+1, sorted_r.end(), S-sorted_r[i]);
        res += std::distance(it, sorted_r.end());
    }
    return res;
}

std::vector<int> generateInput(int n) {
    std::vector<int> r(n);
    for(int i = 0; i < n; ++i) {
        r[i] = i + 1;
    }
    return r;
}