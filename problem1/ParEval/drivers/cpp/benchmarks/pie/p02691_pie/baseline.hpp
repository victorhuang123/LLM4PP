#pragma once

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

ll baseline(ll n, const vector<ll>& a) {
    map<ll, ll> dict;
    vector<vector<ll>> f(n + 1);
    ll amt = 0;
    for (ll i = 1; i <= n; i++) {
        if (!dict[a[i] + i]) {
            amt++;
            dict[a[i] + i] = amt;
        }
        f[dict[a[i] + i]].push_back(i);
    }
    ll cnt = 0;
    for (ll j = 1; j <= n; j++) {
        if (dict[j - a[j]]) {
            ll id = dict[j - a[j]];
            ll pos = lower_bound(f[id].begin(), f[id].end(), j) - f[id].begin();
            cnt += pos;
        }
    }
    return cnt;
}

vector<ll> generateExampleInput(ll n) {
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) {
        a[i] = i;
    }
    return a;
}