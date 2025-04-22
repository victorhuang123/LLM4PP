#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> generateInput() {
    vector<ll> input(MAX);
    for (ll i = 0; i < MAX; ++i) {
        input[i] = i + 1;
    }
    return input;
}

ll baseline(const vector<ll>& input) {
    ll result = 0;
    for (ll i = 0; i < input.size(); ++i) {
        result += input[i];
    }
    return result;
}