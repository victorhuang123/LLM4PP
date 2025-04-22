#pragma once

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll baseline(ll K) {
    set<ll> st;
    ll x = 7 % K;
    ll ct = 1;

    while (true) {
        if (st.count(x)) return -1;
        if (x == 0) return ct;
        st.insert(x);
        x = 10 * x + 7;
        x = (x + K) % K;
        ++ct;
    }
}

ll generateInput() {
    return 1e18;
}