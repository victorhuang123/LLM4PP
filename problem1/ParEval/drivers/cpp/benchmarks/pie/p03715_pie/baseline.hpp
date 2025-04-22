#pragma once

#include <bits/stdc++.h>

using namespace std;

#define ll long long int

ll baseline(ll h, ll w) {
    auto sortt = [](ll &a, ll &b, ll &c) {
        if (a < b) swap(a, b);
        if (b < c) swap(c, b);
        if (a < b) swap(a, b);
    };

    ll i, j, k, s = 1e15;
    ll first, second, third;
    ll w_second = w / 2;
    ll w_third = w - w_second;

    for (i = 1; i < h; i++) {
        first = i * w;
        j = h - i;
        second = j * w_second;
        third = j * w_third;
        sortt(first, second, third);
        s = min(s, first - third);

        first = i * w;
        ll h_second = j / 2;
        ll h_third = j - h_second;
        second = h_second * w;
        third = h_third * w;
        sortt(first, second, third);
        s = min(s, first - third);
    }
    return s;
}

vector<ll> generateInput() {
    return {1000000, 1000000};
}