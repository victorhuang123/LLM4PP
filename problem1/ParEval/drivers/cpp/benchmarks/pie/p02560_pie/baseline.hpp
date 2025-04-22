#pragma once

#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll floor_sum(ll n, ll m, ll a, ll b) {
    ll ans = 0;
    ans += (n - 1) * n * (a / m) / 2 + n * (b / m);
    a %= m;
    b %= m;

    ll y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
    return ans;
}

vector<ll> baseline(int t, const vector<ll>& n, const vector<ll>& m, const vector<ll>& a, const vector<ll>& b) {
    vector<ll> results(t);
    for (int i = 0; i < t; ++i) {
        results[i] = floor_sum(n[i], m[i], a[i], b[i]);
    }
    return results;
}

vector<vector<ll>> generate_input() {
    int t = 1e5;
    vector<ll> n(t, 1e9), m(t, 1e9), a(t, 1e9), b(t, 1e9);
    return {n, m, a, b};
}