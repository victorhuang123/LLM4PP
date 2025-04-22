#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vint;

int baseline(int n, int k, int x, int y) {
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (i <= k) ans += x;
        else ans += y;
    }
    return ans;
}

vector<int> generateInput() {
    int n = 1e8;  // Large n to test efficiency
    int k = 5e7;  // Large k
    int x = 10;   // Arbitrary x
    int y = 5;    // Arbitrary y
    return {n, k, x, y};
}