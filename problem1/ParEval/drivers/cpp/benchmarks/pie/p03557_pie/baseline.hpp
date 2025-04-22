#pragma once

#include<bits/stdc++.h>

#define ll long long

using namespace std;

ll baseline(int n, vector<int>& a, vector<int>& b, vector<int>& c) {
    int tot = 0;
    vector<int> d(n * 3);
    vector<ll> v(n * 3, 0);
    vector<int> e(n);
    ll ans = 0;

    for (int i = 0; i < n; i++)
        d[tot++] = a[i];
    for (int i = 0; i < n; i++)
        d[tot++] = b[i];
    for (int i = 0; i < n; i++)
        d[tot++] = c[i];

    sort(d.begin(), d.begin() + tot);

    auto add = [&](int x, ll y) {
        for (; x <= tot; x += x & (-x)) v[x] += y;
    };

    auto ask = [&](int x) {
        ll s = 0;
        for (; x; x -= x & (-x)) s += v[x];
        return s;
    };

    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(d.begin(), d.begin() + tot, a[i]) - d.begin() + 1;
        add(a[i], 1);
    }

    for (int i = 0; i < n; i++) {
        b[i] = lower_bound(d.begin(), d.begin() + tot, b[i]) - d.begin() + 1;
        e[i] = ask(b[i] - 1);
    }

    fill(v.begin(), v.end(), 0);

    for (int i = 0; i < n; i++)
        add(b[i], e[i]);

    for (int i = 0; i < n; i++) {
        c[i] = lower_bound(d.begin(), d.begin() + tot, c[i]) - d.begin() + 1;
        ans += ask(c[i] - 1);
    }

    return ans;
}

vector<int> generateInput(int n) {
    vector<int> arr(n * 3);
    for (int i = 0; i < n * 3; i++) {
        arr[i] = rand() % 1000000 + 1;
    }
    return arr;
}