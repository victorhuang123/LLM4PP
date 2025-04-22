#pragma once

#include<vector>

long long baseline(int n) {
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0)
            continue;
        else if (i % 5 == 0)
            continue;
        else
            ans += i;
    }
    return ans;
}

std::vector<int> generateInput() {
    std::vector<int> input;
    input.push_back(1000000); // Example input to maximize problem scale
    return input;
}