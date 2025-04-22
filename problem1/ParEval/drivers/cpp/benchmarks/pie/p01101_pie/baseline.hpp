#pragma once

#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll;

ll baseline(ll n, ll m, vector<ll>& a) {
    ll max_sum = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (i != j && a[i] + a[j] <= m) {
                max_sum = max(max_sum, a[i] + a[j]);
            }
        }
    }
    return max_sum == 0 ? -1 : max_sum;
}

vector<ll> generate_input(ll n, ll m) {
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}