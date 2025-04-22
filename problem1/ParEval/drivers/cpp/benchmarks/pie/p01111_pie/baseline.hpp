#pragma once

#include <bits/stdc++.h>

using namespace std;

pair<int, int> baseline(long long b) {
    pair<int, int> ans = {-1, -1};
    for (long long n = 1; n < sqrt(2 * b); ++n) {
        long long a = ((2 * b) / n - n + 1) / 2;
        if (2 * b == n * (2 * a + n - 1)) {
            ans.first = a;
            ans.second = n;
        }
    }
    return ans;
}

vector<long long> generateInput() {
    return {1000000000000LL}; // Example input to maximize problem scale
}