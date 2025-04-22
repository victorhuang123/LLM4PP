#pragma once

#include <bits/stdc++.h>

#define ll long long

using namespace std;

vector<int> generateInput(int n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
    return a;
}

ll baseline(const vector<int>& a) {
    int n = a.size() - 1;
    if (a[0] != -1) return -1;

    for (int i = 1; i <= n; i++) {
        if (a[i] - a[i - 1] > 1) return -1;
    }

    ll ans = 0;

    for (int i = 1; i <= n; i++) {
        if (!a[i]) continue;
        ans++;
        if (a[i - 1] + 1 != a[i]) ans += a[i] - 1;
    }

    return ans;
}