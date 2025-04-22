#pragma once

#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll baseline(ll t, const vector<ll>& arr) {
    ll s = 0;
    for (ll a : arr) {
        s += a;
    }
    if (s > t) return -1;
    else return t - s;
}

vector<ll> generateInput(ll n) {
    vector<ll> arr(n);
    for (ll i = 0; i < n; ++i) {
        arr[i] = 1LL << 30; // Large numbers to maximize computational load
    }
    return arr;
}