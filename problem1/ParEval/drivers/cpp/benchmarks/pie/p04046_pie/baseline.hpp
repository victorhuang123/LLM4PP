#pragma once

#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define mod 1000000007

ll qpow(ll p, ll q) {
    ll f = 1;
    while (q) {
        if (q & 1) f = f * p % mod;
        p = p * p % mod;
        q >>= 1;
    }
    return f;
}

ll baseline(int h, int w, int a, int b) {
    vector<ll> fac(h + w + 1), inv(h + w + 1);
    fac[0] = 1;
    for (int i = 1; i <= h + w; ++i) fac[i] = fac[i - 1] * i % mod;
    inv[h + w] = qpow(fac[h + w], mod - 2);
    for (int i = h + w - 1; i >= 0; --i) inv[i] = inv[i + 1] * (i + 1) % mod;

    auto C = [&](int x, int y) {
        return fac[x] * inv[y] % mod * inv[x - y] % mod;
    };

    ll ans = C(h + w - 2, h - 1);
    for (int i = 0; i < b; ++i) {
        ll temp1 = C(i + h - 1 - a, i);
        ll temp2 = C(w - i + a - 2, a - 1);
        ll temp3 = (temp1 * temp2) % mod;
        ans = (ans - temp3 + mod) % mod;
    }
    return ans;
}