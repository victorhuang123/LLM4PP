#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll baseline(ll n, ll m) {
    ll ans = 0;

    if (m == 0) {
        return n * n;
    }

    for (int j = 1, i = m + 1; i <= n; i++, j++) {
        ans = ans + n / i * j;
        ll tmp = 0;
        tmp = max((ll)0, n % i - m + 1);
        ans = ans + tmp;
    }

    return ans;
}

vector<ll> generateInput() {
    return {1000000000, 1000000};
}