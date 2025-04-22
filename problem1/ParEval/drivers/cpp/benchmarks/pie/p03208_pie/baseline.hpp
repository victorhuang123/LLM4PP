#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

ll baseline(ll n, ll k, vll& v) {
    ll mx = LLONG_MAX;
    sort(v.begin(), v.end());
    for(int i = k-1; i < n; i++) {
        mx = min(v[i] - v[i-k+1], mx);
    }
    return mx;
}

vll generateInput(ll n) {
    vll v(n);
    for(ll i = 0; i < n; i++) {
        v[i] = i + 1;
    }
    return v;
}