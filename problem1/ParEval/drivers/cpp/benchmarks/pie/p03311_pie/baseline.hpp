#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll baseline(int n, vector<int>& num) {
    for (int i = 0; i < n; ++i) {
        num[i] -= i + 1;
    }
    sort(num.begin(), num.end());
    int b = num[n >> 1];
    auto add = [&b](ll s, int x) { return s + abs(x - b); };
    ll sum = accumulate(num.begin(), num.end(), 0LL, add);
    return sum;
}

vector<int> generateInput(int n) {
    vector<int> num(n);
    for (int i = 0; i < n; ++i) {
        num[i] = n - i;
    }
    return num;
}