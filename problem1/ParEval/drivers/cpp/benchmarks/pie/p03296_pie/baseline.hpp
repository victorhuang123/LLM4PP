#pragma once

#include <vector>

using namespace std;

typedef long long ll;

ll baseline(ll n, const vector<ll>& x) {
    ll ans = 0;
    for (ll i = 0; i < n - 1; i++) {
        if (x[i] == x[i + 1]) {
            ans++;
            i++;
        }
    }
    return ans;
}

vector<ll> generateInput(ll n) {
    return vector<ll>(n, 1);
}