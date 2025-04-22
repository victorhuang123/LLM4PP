#pragma once

#include <bits/stdc++.h>

using namespace std;

int64_t baseline(int64_t n, vector<int> a) {
    vector<pair<int, int>> b(4);
    for (int i = 0; i < 4; i++) {
        b[i].first = a[i] << (3 - i);
        b[i].second = i;
    }
    sort(b.begin(), b.end());
    n *= 4;
    int64_t ans = 0;
    while (n) {
        if (n <= 4 && b[0].second == 3) {
            ans += a[b[1].second];
            n -= 1 << b[1].second;
        } else {
            int div = 1 << b[0].second;
            ans += n / div * a[b[0].second];
            n %= div;
        }
    }
    return ans;
}

vector<int> generateInput() {
    return {1000000000, 1000000000, 1000000000, 1000000000};
}