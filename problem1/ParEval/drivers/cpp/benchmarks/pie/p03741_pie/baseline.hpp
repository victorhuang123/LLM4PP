#pragma once

#include <vector>
#include <algorithm>

long long baseline(long long n, const std::vector<long long>& a) {
    long long s = 0, t = 0;
    std::vector<long long> b = a;

    for(int i = 1; i <= n; i++) {
        b[i] += b[i-1];
        if(i % 2) {
            if(b[i] >= 0) t += b[i] + 1, b[i] = -1;
        } else {
            if(b[i] <= 0) t += 1 - b[i], b[i] = 1;
        }
    }

    std::vector<long long> c = a;
    for(int i = 1; i <= n; i++) {
        c[i] += c[i-1];
        if(i % 2) {
            if(c[i] <= 0) s += 1 - c[i], c[i] = 1;
        } else {
            if(c[i] >= 0) s += c[i] + 1, c[i] = -1;
        }
    }

    return std::min(s, t);
}

std::vector<long long> generateInput(long long n) {
    std::vector<long long> a(n + 1);
    for(int i = 1; i <= n; i++) {
        a[i] = i % 1000000;
    }
    return a;
}