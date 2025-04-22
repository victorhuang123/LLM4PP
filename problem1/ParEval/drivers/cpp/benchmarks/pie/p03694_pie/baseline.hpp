#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

int baseline(int N, const std::vector<int>& hh) {
    std::vector<int> sorted_hh = hh;
    std::sort(sorted_hh.begin(), sorted_hh.end());
    std::vector<int> kk(N, 0);

    for (int i = 0; i < N; i++) {
        if (i != 0 && i != N - 1) {
            kk[i] += std::abs(sorted_hh[i] - sorted_hh[N - 1]) * 2;
            kk[i] += std::abs(sorted_hh[i] - sorted_hh[0]);
        } else {
            kk[i] += std::abs(sorted_hh[0] - sorted_hh[N - 1]);
        }
    }

    std::sort(kk.begin(), kk.end());
    return kk[0];
}

std::vector<int> generateInput(int N) {
    std::vector<int> hh(N);
    for (int i = 0; i < N; i++) {
        hh[i] = i + 1;
    }
    return hh;
}