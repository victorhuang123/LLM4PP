#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long

ll baseline(ll n, ll k, vector<ll>& a) {
    ll f[100000], ans = 1e18;
    memset(f, 0x3f, sizeof(f));

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < n; j++)
            f[j] = min(f[j], a[(j - i + n) % n]);
        ll ret = 0;
        for (int j = 0; j < n; ++j) ret += f[j];
        ans = min(ans, ret + 1ll * k * i);
    }

    return ans;
}

vector<ll> generateInput(ll n) {
    vector<ll> a(n);
    for (ll i = 0; i < n; ++i) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}