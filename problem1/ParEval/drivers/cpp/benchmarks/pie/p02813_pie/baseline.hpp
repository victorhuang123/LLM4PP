#pragma once

#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

vector<ll> generateInput(int n) {
    vector<ll> p(n), q(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
        q[i] = n - i;
    }
    return {p, q};
}

ll baseline(int n, const vector<ll>& p, const vector<ll>& q) {
    ll u = 1;
    for (int i = 1; i < n; i++) {
        u *= i;
    }
    ll a = 0;
    ll rp[10];
    memset(rp, 0, sizeof(rp));
    ll b = 0;
    ll rq[10];
    memset(rq, 0, sizeof(rq));
    int t = 0;
    for (ll i = n - 1; i >= 1; i--, t++) {
        int cn = 0;
        for (size_t j = 1; j <= n; j++) {
            if (j == p[t]) {
                rp[j] = 1; break;
            }
            if (rp[j] == 0) cn++;
        }
        a += u * cn;
        int cn2 = 0;
        for (size_t j = 1; j <= n; j++) {
            if (j == q[t]) {
                rq[j] = 1; break;
            }
            if (rq[j] == 0) cn2++;
        }
        b += u * cn2;
        u /= i;
    }
    return abs(a - b);
}