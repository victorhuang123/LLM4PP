#pragma once

#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

#define rep(i,n) for(int i=0;i<(n);++i)

ll baseline(ll n, ll a, ll b, const vector<ll>& x) {
    ll ans = 0;
    rep(i, n-1) ans += min(a * (x[i+1] - x[i]), b);
    return ans;
}

vector<ll> generateInput(ll n) {
    vector<ll> x(n);
    rep(i, n) x[i] = i;
    return x;
}