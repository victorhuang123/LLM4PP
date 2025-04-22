#pragma once

#include<vector>
#include<cmath>

long long baseline(int n, const std::vector<std::vector<int>>& a) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += abs(a[i][0] - a[i-1][0]);
    }
    sum += abs(a[n][0]);
    return sum;
}

std::vector<std::vector<int>> generateInput(int n) {
    std::vector<std::vector<int>> a(n+2, std::vector<int>(2, 0));
    for (int i = 1; i <= n; i++) {
        a[i][0] = i;
    }
    return a;
}