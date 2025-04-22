#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int k) {
    int sum = 0, g;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            g = __gcd(i, j);
            for (int l = 1; l <= k; l++) {
                sum += __gcd(g, l);
            }
        }
    }
    return sum;
}

vector<int> generateInput() {
    return {1000}; // Example input to maximize the problem scale
}