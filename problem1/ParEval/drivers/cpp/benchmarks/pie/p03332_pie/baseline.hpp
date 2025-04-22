#pragma once

#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 3e5 + 5;
const int MOD = 998244353;

int baseline(int n, int a, int b, int k) {
    vector<int> fac(N), ifac(N);

    auto fpow = [](int x, int y) {
        int res = 1;
        while (y) {
            if (y & 1) res = res * x % MOD;
            x = x * x % MOD;
            y >>= 1;
        }
        return res;
    };

    fac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % MOD;
    ifac[N - 1] = fpow(fac[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

    auto C = [&](int k, int n) {
        if (n < k || k < 0) return 0LL;
        return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
    };

    int res = 0;
    for (int x = 0; x <= n; ++x) {
        if ((k - x * a) % b) continue;
        int y = (k - x * a) / b;
        res = (res + C(x, n) * C(y, n)) % MOD;
    }
    return res;
}

vector<int> generateInput() {
    return {300000, 1, 1, 300000};
}