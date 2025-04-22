#pragma once

#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll baseline(ll n, ll k, vector<ll>& a) {
    vector<ll> b = a;
    sort(a.begin(), a.end(), greater<ll>());
    sort(b.begin(), b.end());
    vector<ll> cum(n);
    cum[0] = a[0];
    for (int i = 1; i < n; i++)
        cum[i] = cum[i - 1] + a[i];

    auto valid = [&](ll r) -> pair<bool, ll> {
        ll ans = 0, t = k;
        for (int i = 0; i < n; i++) {
            ll idx = lower_bound(b.begin(), b.end(), r - a[i]) - b.begin();
            if (idx == n) continue;
            idx = n - 1 - idx;
            if (idx < i) continue;
            ll sz = idx - i + 1;
            t -= sz * 2 - 1;
            ll sum = cum[idx];
            if (i) sum -= cum[i - 1];
            ans += sum * 2 + a[i] * (sz - 1) * 2;
        }
        return {t >= 0, ans};
    };

    ll s = 0, e = 2e5 + 5;
    while (s < e) {
        ll mid = (s + e) / 2;
        auto [isValid, _] = valid(mid);
        if (isValid) e = mid;
        else s = mid + 1;
    }

    auto [_, ans] = valid(s);
    return ans + (k - valid(s).second) * (s - 1);
}

vector<ll> generateInput(ll n) {
    vector<ll> a(n);
    for (ll i = 0; i < n; i++)
        a[i] = rand() % 1000000 + 1;
    return a;
}