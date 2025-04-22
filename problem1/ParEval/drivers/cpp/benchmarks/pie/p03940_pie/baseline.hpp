#pragma once

#include<bits/stdc++.h>

#define N 111111
#define M 444444
#define LL long long

using namespace std;

LL baseline(int n, LL E, LL T, vector<LL>& a) {
    vector<LL> f(N), V1(M, 1e18), V2(M, 1e18);
    int i, k;

    auto ins = [&](int k, int l, int r, int x, LL z1, LL z2) {
        if (l == r) { V1[k] = z1; V2[k] = z2; return; }
        int md = l + r >> 1;
        if (x <= md) ins(k << 1, l, md, x, z1, z2);
        else ins(k << 1 | 1, md + 1, r, x, z1, z2);
        V1[k] = min(V1[k << 1], V1[k << 1 | 1]);
        V2[k] = min(V2[k << 1], V2[k << 1 | 1]);
    };

    auto qu1 = [&](int k, int l, int r, int x, int y) -> LL {
        if (x > y) return 1e18;
        if (x <= l && r <= y) return V1[k];
        int md = l + r >> 1;
        if (y <= md) return qu1(k << 1, l, md, x, y);
        if (x > md) return qu1(k << 1 | 1, md + 1, r, x, y);
        return min(qu1(k << 1, l, md, x, y), qu1(k << 1 | 1, md + 1, r, x, y));
    };

    auto qu2 = [&](int k, int l, int r, int x, int y) -> LL {
        if (x > y) return 1e18;
        if (x <= l && r <= y) return V2[k];
        int md = l + r >> 1;
        if (y <= md) return qu2(k << 1, l, md, x, y);
        if (x > md) return qu2(k << 1 | 1, md + 1, r, x, y);
        return min(qu2(k << 1, l, md, x, y), qu2(k << 1 | 1, md + 1, r, x, y));
    };

    for (i = 0, k = 0; i <= n; i++) {
        f[i] = 1e18;
        for (; (a[i] - a[k + 1]) * 2 > T && k < i; k++);
        if (i == 0) f[i] = 0;
        else f[i] = min(qu1(1, 0, n, k, i - 1) + T + a[i], qu2(1, 0, n, 0, k - 1) + 1ll * a[i] * 3);
        ins(1, 0, n, i, f[i] - a[i], f[i] - a[i] - a[i + 1] * 2);
    }

    return f[n];
}

vector<LL> generateInput(int n, LL E, LL T) {
    vector<LL> a(n + 1);
    for (int i = 0; i <= n; i++) {
        a[i] = i * 100000LL;
    }
    return a;
}