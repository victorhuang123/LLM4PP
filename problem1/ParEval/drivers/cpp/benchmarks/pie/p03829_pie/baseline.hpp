#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> generateInput() {
    ll N = 1e6;
    ll A = 1e9;
    ll B = 1e9;
    vector<ll> X(N);
    for (ll i = 0; i < N; i++) {
        X[i] = i * 1e3;
    }
    return X;
}

ll baseline(ll N, ll A, ll B, vector<ll>& X) {
    ll kotae = 0;
    for (ll i = 0; i < N - 1; i++) {
        kotae += min((X[i + 1] - X[i]) * A, B);
    }
    return kotae;
}