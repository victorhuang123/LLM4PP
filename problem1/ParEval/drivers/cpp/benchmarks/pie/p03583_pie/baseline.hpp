#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

tuple<ll, ll, ll> baseline(ll N) {
    for (int i = 0; i < 3500; ++i) {
        for (int j = 0; j < 3500; ++j) {
            ll h = i + 1;
            ll n = j + 1;
            ll x = N * h * n;
            ll y = 4 * h * n - N * n - N * h;
            if (y <= 0 || x < y || x <= 0) continue;
            if (x % y == 0) {
                return make_tuple(h, n, x / y);
            }
        }
    }
    return make_tuple(0, 0, 0);
}

ll generateInput() {
    return 1000000000LL;
}