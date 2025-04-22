#pragma once

#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

long long baseline(int n, int m) {
    if (abs(n - m) > 1) return 0;
    
    long long sum = 1, cnt = 1;
    for (int i = 1; i <= n; i++) {
        sum = (sum * i) % mod;
    }
    for (int i = 1; i <= m; i++) {
        cnt = (cnt * i) % mod;
    }
    long long p = (cnt * sum) % mod;
    if (m == n) p = (p * 2) % mod;
    return p;
}

vector<int> generateInput() {
    return {100000, 100000};
}