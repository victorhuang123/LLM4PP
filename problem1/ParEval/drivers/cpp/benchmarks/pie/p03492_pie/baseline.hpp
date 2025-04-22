#pragma once

#include<bits/stdc++.h>

#define ll long long
#define N 5010
#define mod 1000000007

using namespace std;

ll baseline(int n, int a[], int cnt) {
    ll jc[N], inv[N];

    auto K = [](ll x, int y = mod - 2) {
        ll t = 1; 
        for (; y; y >>= 1, x = x * x % mod) 
            if (y & 1) t = t * x % mod; 
        return t;
    };

    auto C = [&](int x, int y) {
        return jc[x] * inv[y] % mod * inv[x - y] % mod;
    };

    auto U = [](ll &x, int y) {
        if ((x += y) >= mod) x -= mod;
    };

    auto doit = [&](int cc, int a[]) {
        ll f[N], g[N];
        memset(f, 0, sizeof f); 
        f[0] = 1; 
        int tot = 0;

        for (int i = 1; i <= cc; ++i) {
            memset(g, 0, sizeof g);
            for (int j = 0; j <= a[i]; ++j)
                for (int k = tot; ~k; --k)
                    U(g[k + j], f[k] * C(a[i], j) % mod * C(a[i], j) % mod * jc[j] % mod);
            tot += a[i];
            memcpy(f, g, sizeof g);
        }

        for (int i = tot; ~i; --i) f[i] = f[i] * jc[tot - i] % mod;
        for (int i = tot; ~i; --i) {
            for (int j = i - 1; ~j; --j)
                U(f[j], mod - f[i] * C(i, j) % mod);
        }

        return f[0];
    };

    jc[0] = 1; 
    for (int i = 1; i < N; ++i) jc[i] = jc[i - 1] * i % mod;
    inv[N - 1] = K(jc[N - 1]); 
    for (int i = N; i--;) inv[i - 1] = inv[i] * i % mod;

    ll result = (doit(cnt, a) + doit(cnt - 1, a)) % mod;
    return result;
}

vector<int> generateInput(int n) {
    vector<int> a(n, 5000);
    return a;
}