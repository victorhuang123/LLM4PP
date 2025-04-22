#pragma once

#include<bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

ll baseline(ll n, vector<ll>& a) {
    ll ans = 0;
    sort(a.begin(), a.end());
    for(ll i = 0; i < n; i++) {
        ll term1 = (a[i] * (1LL << (n - 1))) % mod;
        ll term2 = (1LL << i) % mod;
        ll term3 = (n - i + 1) % mod;
        ll term4 = (1LL << (n - i - 1)) % mod;
        ans = (ans + (((term1 * term2) % mod * term3) % mod * term4) % mod;
    }
    return ans;
}

vector<ll> generateInput(ll n) {
    vector<ll> a(n);
    for(ll i = 0; i < n; i++) {
        a[i] = rand() % mod;
    }
    return a;
}