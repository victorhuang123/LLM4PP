#pragma once

#include <bits/stdc++.h>

using namespace std;

using LL = long long;

#define MOD (7 + (int)1e9)

LL baseline(LL N, LL M) {
    vector<LL> f(max(N, M) + 2);
    f[1] = 1;
    for (int i = 1; i <= max(N, M); ++i) {
        f[i+1] = (f[i] * (i+1)) % MOD;
    }

    LL res;
    if (labs(N - M) >= 2) {
        res = 0;
    } else if (labs(N - M) == 1) {
        res = ((f[N] % MOD) * (f[M] % MOD)) % MOD;
    } else {
        res = ((f[N] % MOD) * (f[M] % MOD) * 2) % MOD;
    }
    return res;
}

vector<LL> generateInput() {
    return {100000, 99999};
}