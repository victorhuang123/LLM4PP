#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long ll;

ll baseline(ll n) {
    ll ans = LLONG_MAX;
    for (ll i = 1; i < n; i++) {
        ll sum = 0;
        ll x = i;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        x = n - i;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        ans = min(ans, sum);
    }
    return ans;
}

vector<ll> generateInput() {
    return {1000000000000000LL};
}