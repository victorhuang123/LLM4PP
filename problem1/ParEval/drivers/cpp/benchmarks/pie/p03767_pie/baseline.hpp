#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); i++)

#define all(v) v.begin(), v.end()

#define allr(v) v.rbegin(), v.rend()

ll baseline(ll n, vector<ll>& a) {
    sort(all(a));
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[n + 2 * i];
    }
    return ans;
}

vector<ll> generateInput(ll n) {
    vector<ll> a(3 * n);
    rep(i, 3 * n) {
        a[i] = rand() % 1000000;
    }
    return a;
}