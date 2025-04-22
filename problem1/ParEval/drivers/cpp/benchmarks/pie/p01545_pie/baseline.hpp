#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAX 100005

struct BIT {
    void init() { memset(bit, 0, sizeof(bit)); }
    ll bit[MAX];

    void set(int r, ll x) {
        r = MAX - r - 1;
        while (r) {
            bit[r] = max(bit[r], x);
            r -= (r & -r);
        }
    }

    ll get(int i) {
        i = MAX - i - 1;
        ll res = 0;
        while (i < MAX) {
            res = max(res, bit[i]);
            i += (i & -i);
        }
        return res;
    }
};

ll baseline(int n, const vector<ll>& a) {
    BIT A;
    A.init();
    ll sum = 0, ans = 0;

    for (int i = 0; i < n; i++) {
        sum += a[i];
        ll k = A.get(a[i]);
        ans = max(ans, k + a[i]);
        A.set(a[i], k + a[i]);
    }

    return sum - ans;
}

vector<ll> generateInput(int n) {
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}