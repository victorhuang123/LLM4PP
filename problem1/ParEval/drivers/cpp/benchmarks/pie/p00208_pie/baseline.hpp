#pragma once

#include<vector>
#include<cmath>

std::vector<int> generateInput() {
    return {1000000}; // Example input to maximize the problem scale
}

std::vector<int> baseline(int n) {
    std::vector<int> a = {0, 1, 2, 3, 5, 7, 8, 9};
    std::vector<int> result;
    int i;
    for (i = 0; pow(8, i) <= n; i++);
    for (i--; i >= 0; i--) {
        result.push_back(a[n / (int)pow(8, i)]);
        n %= (int)pow(8, i);
    }
    return result;
}