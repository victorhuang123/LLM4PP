#pragma once

#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

vector<int> baseline(int n, int x) {
    vector<int> result;
    int t = 1;
    if (x == 1 || x == 2 * n - 1) {
        return result;
    }
    for (int i = 1; i < n - 1; i++) {
        while (t == x || t == x - 1 || t == x + 1) t++;
        result.push_back(t++);
    }
    result.push_back(x - 1);
    result.push_back(x);
    result.push_back(x + 1);
    for (int i = 1; i < n - 1; i++) {
        while (t == x || t == x - 1 || t == x + 1) t++;
        result.push_back(t++);
    }
    return result;
}

vector<int> generateInput() {
    int n = 100000; // Large n to test efficiency
    int x = 50000;  // Middle value to maximize problem scale
    return {n, x};
}