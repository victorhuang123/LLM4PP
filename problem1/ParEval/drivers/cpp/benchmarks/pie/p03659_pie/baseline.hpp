#pragma once

#include<vector>
#include<algorithm>
#include<cmath>
#include<climits>

long long baseline(int n, const std::vector<int>& t_values) {
    std::vector<long long> a(n + 1, 0);
    long long total = 0;
    for (int i = 1; i <= n; i++) {
        total += t_values[i - 1];
        a[i] = a[i - 1] + t_values[i - 1];
    }
    long long minn = LLONG_MAX;
    for (int i = 2; i <= n; i++) {
        minn = std::min(minn, std::abs(total - (a[i - 1] * 2)));
    }
    return minn;
}

std::vector<int> generateInput(int n) {
    std::vector<int> t_values(n);
    for (int i = 0; i < n; i++) {
        t_values[i] = rand() % 1000000 + 1;
    }
    return t_values;
}