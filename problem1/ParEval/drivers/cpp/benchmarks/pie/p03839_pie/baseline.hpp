#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll baseline(int N, int K, vector<int>& a) {
    vector<ll> s(N + 1, 0);
    vector<ll> sa(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        s[i] = s[i - 1] + a[i - 1];
        sa[i] = sa[i - 1] + max(a[i - 1], 0);
    }

    ll kotae = 0;
    for (int i = 1; i <= N - K + 1; i++) {
        ll kari = max(s[i + K - 1] - s[i - 1], 0ll) + sa[i - 1] + sa[N] - sa[i + K - 1];
        kotae = max(kotae, kari);
    }
    return kotae;
}

vector<int> generateInput(int N) {
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = (i % 2 == 0) ? (i + 1) : -(i + 1);
    }
    return a;
}