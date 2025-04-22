#pragma once

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

vector<ll> baseline(int N, const vector<ll>& a) {
    vector<ll> l(N + 1), but(N + 1, 0), idx(N + 1, LLONG_MAX), ans(N + 1, 0);
    for (int i = 1; i <= N; ++i) l[i] = a[i - 1];
    sort(l.begin() + 1, l.begin() + N + 1);
    auto last = unique(l.begin() + 1, l.begin() + N + 1);
    l.resize(distance(l.begin(), last));
    for (int i = 1; i <= N; ++i) {
        ll val = a[i - 1];
        ll pos = lower_bound(l.begin() + 1, l.end(), val) - l.begin();
        but[pos]++;
        idx[pos] = min((ll)i, idx[pos]);
    }
    for (int i = l.size() - 1; i >= 1; --i) {
        if (but[i]) {
            but[i - 1] += but[i];
            idx[i - 1] = min(idx[i], idx[i - 1]);
            ans[idx[i] - 1] += (ll)(l[i] - (i > 1 ? l[i - 1] : 0)) * but[i];
        }
    }
    return ans;
}

vector<ll> generateInput(int N) {
    vector<ll> a(N);
    for (int i = 0; i < N; ++i) {
        a[i] = i + 1;
    }
    return a;
}