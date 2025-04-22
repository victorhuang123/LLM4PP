#pragma once

#include <bits/stdc++.h>

#define ll long long

using namespace std;

ll baseline(ll n, ll x) {
    ll base = n;
    ll repeat = n - x;
    ll ans = x;

    if (base % repeat == 0) {
        ans += ((base / repeat) - 1) * 2 * repeat;
        return ans;
    }

    if (base % repeat != 0) {
        ans += (((base / repeat) * 2 * repeat) - repeat);
        ll temp = base;
        base = repeat;
        repeat = temp % repeat;
    }

    while (base % repeat != 0) {
        ans += ((base / repeat) * 2 * repeat);
        ll temp = base;
        base = repeat;
        repeat = temp % repeat;
    }

    ans += ((base / repeat) * 2 * repeat);
    ans -= repeat;
    return ans;
}

ll generateInput() {
    return baseline(1000000000000LL, 999999999999LL);
}