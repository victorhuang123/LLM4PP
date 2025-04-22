#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> generateInput() {
    vector<ll> input;
    for (ll i = 1; i <= 1000000; ++i) {
        input.push_back(i);
    }
    return input;
}

ll baseline(ll r) {
    return 3 * r * r;
}