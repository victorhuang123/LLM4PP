#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

typedef long long ll;

ll baseline(ll N, ll K, const vector<ll>& a) {
    ll gcd = a[0];
    ll maxV = 0;

    for (ll i = 0; i < N; ++i) {
        maxV = max(maxV, a[i]);
    }

    for (int i = 1; i < N; ++i) {
        gcd = gcd ? gcd : a[i];
        gcd = __gcd(gcd, a[i]);
    }

    if (K % gcd == 0 && maxV >= K) {
        return 1; // POSSIBLE
    } else {
        return 0; // IMPOSSIBLE
    }
}

vector<ll> generateInput() {
    ll N = 1e5;
    ll K = 1e12;
    vector<ll> a(N, 1e6);
    return a;
}