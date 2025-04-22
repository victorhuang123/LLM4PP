#pragma once

#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9+7;

int add(int a, int b) {
    return a + b < mod ? a + b : a + b - mod;
}

int mul(int a, int b) {
    return int(1LL * a * b % mod);
}

int fexp(int b, int e = mod - 2) {
    int ans = 1;
    while(e) {
        if(e & 1) ans = mul(ans, b);
        b = mul(b, b);
        e /= 2;
    }
    return ans;
}

using ll = long long;
const ll oo = 1e18;
const int N = 200005;

struct Segtree {
    ll st[2 * N];
    int n;

    ll query(int l, int r) { // [l, r]
        ll ans = -oo;
        for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ans = max(ans, st[l++]);
            if(r & 1) ans = max(ans, st[--r]);
        }
        return ans;
    }

    void build() {
        for(int i = 0; i < 2 * N; i++) st[i] = -oo;
    }

    void update(int p, ll val) {
        p += n;
        st[p] = max(st[p], val);
        while(p >>= 1) st[p] = max(st[2*p], st[2*p+1]);
    }
};

ll baseline(int n, vector<ll>& x, vector<ll>& y) {
    Segtree up, down;
    up.n = down.n = n;
    up.build(), down.build();

    vector<ll> compr(n);
    for(int i = 0; i < n; i++) {
        compr[i] = y[i];
    }
    sort(compr.begin(), compr.end());

    vector<int> id(n);
    for(int i = 0; i < n; i++) id[i] = i;
    sort(id.begin(), id.end(), [&](int i, int j) {
        if(x[i] != x[j]) return x[i] < x[j];
        return y[i] < y[j];
    });

    ll ans = 0;

    for(int w = 0; w < n; w++) {
        int i = id[w];
        int me = int(lower_bound(compr.begin(), compr.end(), y[i]) - compr.begin();

        ans = max(ans, up.query(me, n - 1) + x[i] - y[i]);
        ans = max(ans, down.query(0, me) + x[i] + y[i]);

        up.update(me, y[i] - x[i]);
        down.update(me, -y[i] - x[i]);
    }

    return ans;
}

vector<ll> generateInput(int n) {
    vector<ll> x(n), y(n);
    for(int i = 0; i < n; i++) {
        x[i] = rand() % 1000000;
        y[i] = rand() % 1000000;
    }
    return {x, y};
}