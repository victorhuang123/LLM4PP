#pragma once

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll baseline(ll n, ll x, vector<ll>& a) {
    ll ans = 0LL;
    for(ll i = 1; i < n; i++) {
        ll s = a[i] + a[i-1];
        if(s > x) {
            ans += s - x;
            a[i] -= (s - x);
        }
    }
    return ans;
}

vector<ll> generateInput(ll n, ll x) {
    vector<ll> a(n, x);
    return a;
}