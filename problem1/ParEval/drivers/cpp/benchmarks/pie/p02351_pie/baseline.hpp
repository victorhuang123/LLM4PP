#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct query {
    int type; // 0=empty, 1=add
    ll value;
    query(int a=0, ll b=0) : type(a), value(b) {}
};

ll baseline(int n, int q, vector<int>& types, vector<int>& a, vector<int>& b, vector<ll>& x) {
    query s[(1 << 18)];
    ll t[(1 << 18)] = {0};

    auto compute = [&](int k, int l, int r) {
        query q = s[k];
        s[k].type = s[k].value = 0;
        if (q.type == 0 || r - l == 1) return;

        int m = (l + r) / 2;

        s[k * 2 + 1].type = 1;
        s[k * 2 + 1].value += q.value;
        t[k * 2 + 1] += q.value * (m - l);

        s[k * 2 + 2].type = 1;
        s[k * 2 + 2].value += q.value;
        t[k * 2 + 2] += q.value * (r - m);
    };

    auto Add = [&](int a, int b, ll x, int k, int l, int r) {
        if (b <= l || r <= a) return;
        compute(k, l, r);
        if (a <= l && r <= b) {
            s[k] = query(1, x);
            t[k] += x * (r - l);
        } else {
            int m = (l + r) / 2;
            Add(a, b, x, k * 2 + 1, l, m);
            Add(a, b, x, k * 2 + 2, m, r);
            t[k] = t[k * 2 + 1] + t[k * 2 + 2];
        }
    };

    auto Get = [&](int a, int b, int k, int l, int r) {
        if (b <= l || r <= a) return 0LL;
        compute(k, l, r);
        if (a <= l && r <= b) {
            return t[k];
        } else {
            int m = (l + r) / 2;
            ll lv = Get(a, b, k * 2 + 1, l, m);
            ll rv = Get(a, b, k * 2 + 2, m, r);
            return lv + rv;
        }
    };

    ll result = 0;
    for (int i = 0; i < q; ++i) {
        if (types[i] == 0) {
            Add(a[i], b[i] + 1, x[i], 0, 0, (1 << 17));
        } else {
            result += Get(a[i], b[i] + 1, 0, 0, (1 << 17));
        }
    }
    return result;
}

vector<int> generateInput(int n, int q) {
    vector<int> types(q), a(q), b(q);
    vector<ll> x(q);
    for (int i = 0; i < q; ++i) {
        types[i] = rand() % 2;
        a[i] = rand() % n;
        b[i] = a[i] + rand() % (n - a[i]);
        x[i] = rand() % 1000000;
    }
    return {types, a, b, x};
}