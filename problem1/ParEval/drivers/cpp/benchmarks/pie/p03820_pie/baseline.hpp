#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MOD = 1E9 + 7;

ll modExp(ll e, ll n, ll m = MOD) {
    ll ret = 1;
    for (; n; n >>= 1, e = e * e % m)
        if (n & 1)
            ret = ret * e % m;
    return ret;
}

int baseline(int n, int k) {
    vector<vector<int>> f(k, vector<int>(n, 0));
    vector<ll> inv(n + 1), fac(n + 1), facinv(n + 1);

    inv[0] = 0, inv[1] = 1;
    fac[0] = fac[1] = 1;
    facinv[0] = facinv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        fac[i] = fac[i - 1] * i % MOD;
        facinv[i] = facinv[i - 1] * inv[i] % MOD;
    }

    f[0][0] = 1;
    for (int i = 1; i < k; ++i) {
        int s = f[i - 1][i - 1];
        for (int j = i; j < n; ++j) {
            f[i][j] = (f[i][j] + s) % MOD;
            f[i][j] = (f[i][j] + f[i - 1][j]) % MOD;
            s = (s + f[i - 1][j]) % MOD;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans = (ans + f[k - 1][i]) % MOD;
    return ans * modExp(2, max(0, n - k - 1)) % MOD;
}

vector<int> generateInput() {
    return {2000, 1000};
}