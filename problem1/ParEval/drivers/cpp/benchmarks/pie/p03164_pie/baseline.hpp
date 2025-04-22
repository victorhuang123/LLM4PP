#pragma once

#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

#define ll long long

#define li long

#define pb push_back

#define mem(arr,x) memset(arr,x,sizeof(arr))

ll dp[101][100010];
bool vis[101][100010];

ll minWeight(ll end, ll Val, const vector<ll>& w, const vector<ll>& v) {
    if (Val <= 0)
        return 0;
    if (end == 0)
        return INT_MAX;
    if (vis[end][Val])
        return dp[end][Val];
    vis[end][Val] = 1;
    return dp[end][Val] = min(w[end-1] + minWeight(end-1, Val-v[end-1], w, v), minWeight(end-1, Val, w, v));
}

ll baseline(ll n, ll W, const vector<ll>& w, const vector<ll>& v) {
    ll totalV = 0;
    for (ll i = 0; i < n; i++) {
        totalV += v[i];
    }
    mem(vis, 0);
    for (ll i = 0; i <= n; i++) {
        for (ll j = 0; j <= totalV; j++) {
            dp[i][j] = INT_MAX;
        }
    }
    for (ll i = totalV; i >= 1; i--) {
        if (minWeight(n, i, w, v) <= W) {
            return i;
        }
    }
    return 0;
}

vector<ll> generateInput(ll n) {
    vector<ll> w(n), v(n);
    for (ll i = 0; i < n; i++) {
        w[i] = rand() % 1000 + 1;
        v[i] = rand() % 1000 + 1;
    }
    return {w, v};
}