#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<ll>> dp;

ll f(ll pos, ll colour, ll n, ll k) {
    if (pos == n - 1) {
        return 1;
    }
    if (dp[pos][colour] != -1) {
        return dp[pos][colour];
    }
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        if (i != colour)
            ans += f(pos + 1, i, n, k);
    }
    return dp[pos][colour] = ans;
}

ll baseline(ll n, ll k) {
    dp.assign(n, vector<ll>(k, -1));
    ll ans = f(0, 0, n, k);
    return ans * k;
}

vector<ll> generateInput() {
    return {1000, 1000};
}