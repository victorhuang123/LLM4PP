#pragma once

#include <vector>
#include <algorithm>

int baseline(int n, int c, int k, std::vector<int>& p) {
    std::sort(p.begin(), p.end());
    long long ans = 1;
    int t = 0;
    int sum = 1;
    for (int i = 1; i < n; i++) {
        if (p[i] <= p[t] + k && sum < c) {
            sum++;
        } else {
            sum = 1;
            ans++;
            t = i;
        }
    }
    return ans;
}

std::vector<int> generateInput(int n) {
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = rand() % 1000000;
    }
    return p;
}