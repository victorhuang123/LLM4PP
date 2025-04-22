#pragma once

#include <bits/stdc++.h>

using namespace std;

using VI = vector<int>;

int baseline(int n, int t, VI& a) {
    VI prof(n);
    int mn = a[0];
    for (int i = 1; i < n; ++i) {
        prof[i] = a[i] - mn;
        mn = min(mn, a[i]);
    }
    int mx = *max_element(prof.begin(), prof.end());
    return count(prof.begin(), prof.end(), mx);
}

VI generateInput(int n) {
    VI a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % 1000000;
    }
    return a;
}