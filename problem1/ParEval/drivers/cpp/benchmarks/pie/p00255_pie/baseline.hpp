#pragma once

#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll;

vector<ll> generateInput(ll n) {
    vector<ll> input(2 * n - 1);
    for (ll i = 0; i < n; ++i) {
        input[i] = 1; // Example input for p
    }
    for (ll i = n; i < 2 * n - 1; ++i) {
        input[i] = i - n + 1; // Example input for l
    }
    return input;
}

ll baseline(ll n, const vector<ll>& input) {
    ll num = n, len = 0;
    for (ll i = 0; i < n; ++i) {
        len += input[i];
    }

    vector<ll> l(input.begin() + n, input.end());
    sort(l.begin(), l.end());

    for (ll i = n - 2; i >= 0; --i) {
        if ((num - 1) * (len + l[i]) < num * len) break;
        num--;
        len += l[i];
    }
    return num * len;
}