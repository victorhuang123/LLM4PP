#pragma once

#include<vector>
#include<algorithm>

long long baseline(long long n, long long T, const std::vector<long long>& t) {
    long long sum = 0;
    for (long long i = 1; i < n; i++) {
        if (t[i] - t[i-1] >= T)
            sum += T;
        else
            sum += t[i] - t[i-1];
    }
    sum += T;
    return sum;
}

std::vector<long long> generateInput(long long n) {
    std::vector<long long> t(n);
    for (long long i = 0; i < n; i++) {
        t[i] = i * 1000000000LL;
    }
    return t;
}