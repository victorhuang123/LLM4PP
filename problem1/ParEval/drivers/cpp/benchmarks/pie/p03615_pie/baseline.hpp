#pragma once

#include<vector>
#define mod 998244353

int baseline(const std::vector<int>& x, const std::vector<int>& y) {
    int n = x.size();
    int ans = ((1 << n) - (1LL * n * (n - 1) >> 1) % mod - n - 1) % mod + mod) % mod;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int sum = 0;
            for (int k = j + 1; k < n; k++) {
                if (k == i || k == j) continue;
                int a = 1LL * (y[j] - y[i]) * (x[k] - x[j]) % mod;
                int b = 1LL * (y[k] - y[j]) * (x[j] - x[i]) % mod;
                if (a == b) sum++;
            }
            ans = (ans - (1 << sum) + 1 + mod) % mod;
        }
    }
    return ans;
}

std::vector<std::vector<int>> generateInput() {
    int n = 1000; // Maximum problem scale
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        x[i] = i;
        y[i] = i * i;
    }
    return {x, y};
}