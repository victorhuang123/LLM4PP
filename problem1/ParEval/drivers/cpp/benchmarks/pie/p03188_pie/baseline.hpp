#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> baseline(int k) {
    vector<vector<int>> result;
    if (k <= 500) {
        result.resize(k, vector<int>(k));
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                result[i][j] = i + 1;
            }
        }
    } else {
        int n = ((k + 3) / 4) * 2;
        result.resize(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int res = (i + j + 2) % n + (i % 2 == 0 ? 0 : n) + 1;
                if (res > k) res -= n;
                result[i][j] = res;
            }
        }
    }
    return result;
}

vector<int> generateInput() {
    return {1000}; // Example input to maximize the problem scale
}