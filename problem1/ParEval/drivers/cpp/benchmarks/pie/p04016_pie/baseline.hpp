#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll baseline(ll n, ll s) {
    auto check = [](ll x, ll n, ll s) {
        if (x == 1) return false;
        ll tt = 0, ts = n;
        while (ts) {
            tt += ts % x;
            ts /= x;
        }
        return tt == s;
    };

    ll ans = 10000000000000ll;
    if (n == s) {
        return n + 1;
    }
    for (int i = 1; i <= sqrt(n); i++) {
        if ((n - s + i) % i == 0 && i * i < n) {
            if (((n - s + i) / i))
                if (n / ((n - s + i) / i) == i)
                    ans = min(ans, (n - s + i) / i);
        }
        if (check(i, n, s)) ans = min(ans, (ll)i);
    }
    return ans == 10000000000000ll ? -1 : ans;
}

vector<ll> generateInput() {
    return {1000000000000, 999999999999};
}