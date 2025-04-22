#pragma once

#include <vector>

std::vector<long> baseline(long n, const std::vector<long>& tn, long m, const std::vector<long>& pm, const std::vector<long>& xm) {
    long sumt = 0;
    for (int i = 0; i < n; i++) {
        sumt += tn[i];
    }
    std::vector<long> result(m);
    for (int i = 0; i < m; i++) {
        result[i] = sumt - tn[pm[i] - 1] + xm[i];
    }
    return result;
}

std::vector<long> generateInput(long n, long m) {
    std::vector<long> tn(n, 1);
    std::vector<long> pm(m);
    std::vector<long> xm(m, 1);
    for (long i = 0; i < m; i++) {
        pm[i] = i % n + 1;
    }
    return baseline(n, tn, m, pm, xm);
}