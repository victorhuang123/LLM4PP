#pragma once

#include <vector>

using ll = long long;

ll invmod(ll a, ll p) {
    ll b = p, u = 1, v = 0;
    while (b) {
        ll t = a / b;
        a -= t * b; std::swap(a, b);
        u -= t * v; std::swap(u, v);
    }
    u %= p;
    if (u < 0) u += p;
    return u;
}

std::vector<ll> baseline(ll p, const std::vector<ll>& a) {
    std::vector<ll> b(p, 0);
    b[0] = a[0];
    ll inv = invmod(p-1, p);
    std::vector<ll> temp_a = a;
    for (ll i = 0; i < p; i++) temp_a[i] = (temp_a[i] - b[0] + p) % p;
    for (ll i = p-1; i > 0; i--) {
        for (ll j = 1; j < p; j++) b[i] += temp_a[j];
        b[i] = b[i] * inv % p;
        for (ll j = 1; j < p; j++) temp_a[j] = temp_a[j] * j % p;
    }
    return b;
}

std::vector<ll> generate_input(ll p) {
    std::vector<ll> a(p);
    for (ll i = 0; i < p; i++) {
        a[i] = i;
    }
    return a;
}