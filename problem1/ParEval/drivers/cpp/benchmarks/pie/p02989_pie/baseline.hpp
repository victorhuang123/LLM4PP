#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> generateInput(int n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        a[i] = i;
    }
    return a;
}

int baseline(int n, vector<int>& a) {
    sort(a.begin() + 1, a.end());
    int ans = 0;
    for (int i = 1; i <= 1e5; i++) {
        int lo = 1, hi = n, ret = 0, key = i;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (a[mid] >= key) ret = mid, hi = mid - 1;
            else lo = mid + 1;
        }
        int big = n - ret + 1;
        int small = n - big;
        if (big == small) ans++;
    }
    return ans;
}