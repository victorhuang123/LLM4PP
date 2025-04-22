#pragma once

#include<vector>
#include<cmath>

int baseline(int n, const std::vector<int>& a) {
    int odd = 0, even = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) even++;
        else odd++;
    }
    int ans = pow(3, n);
    ans -= pow(2, even);
    return ans;
}

std::vector<int> generateInput(int n) {
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1; // Example input: 1, 2, 3, ..., n
    }
    return a;
}