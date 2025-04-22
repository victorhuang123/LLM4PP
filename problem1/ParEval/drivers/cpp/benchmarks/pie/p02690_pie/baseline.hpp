#pragma once

#include <utility>
#include <vector>

using ll = long long;

std::pair<ll, ll> baseline(ll x) {
    for(ll i = 0; i <= 200; i++) {
        for(ll j = -i; j <= i; j++) {
            ll a = i * i * i * i * i;
            ll b = j * j * j * j * j;
            if(a - b == x) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}

ll generateExampleInput() {
    return 1234567890123456789LL;
}