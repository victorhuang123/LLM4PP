#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int baseline(ll x, ll y) {
    if(x <= 1 && y <= 1) return 0;
    else if(abs(x - y) <= 1) return 0;
    else return 1;
}

vector<pair<ll, ll>> generate_input() {
    vector<pair<ll, ll>> inputs;
    for (ll i = 0; i < 1000; ++i) {
        inputs.push_back({i, i + 1});
    }
    return inputs;
}