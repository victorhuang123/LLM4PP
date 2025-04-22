#pragma once

#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

ll baseline(ll x, ll y, ll a, ll b, ll c, vector<ll>& p, vector<ll>& q, vector<ll>& r) {
    ll ans = 0;

    sort(p.begin(), p.end(), greater<ll>());
    sort(q.begin(), q.end(), greater<ll>());

    for (int i = 0; i < x; i++) r.push_back(p[i]);
    for (int i = 0; i < y; i++) r.push_back(q[i]);

    sort(r.begin(), r.end(), greater<ll>());

    for (int i = 0; i < x + y; i++) ans += r[i];

    return ans;
}

vector<ll> generateInput(ll size, ll minVal, ll maxVal) {
    vector<ll> arr(size);
    for (ll i = 0; i < size; i++) {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    }
    return arr;
}