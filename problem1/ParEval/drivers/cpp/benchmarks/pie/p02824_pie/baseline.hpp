#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> generateInput(ll n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}

int baseline(ll n, ll m, ll v, ll p, vector<int>& a) {
    sort(a.begin() + 1, a.end());
    vector<ll> sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + a[i];
    }
    int ans = p;
    for (int i = n - p; i >= 1; --i) {
        if (a[i] + m < a[n - p + 1]) break;
        else {
            if (m * v <= i * m + (p - 1) * m + (a[i] + m) * (n - p + 1 - i) - (sum[n - p + 1] - sum[i])) {
                ans++;
            } else break;
        }
    }
    return ans;
}