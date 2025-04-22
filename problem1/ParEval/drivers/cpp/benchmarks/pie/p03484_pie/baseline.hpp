#pragma once

#include <bits/stdc++.h>

typedef long long int ll;
typedef long double ld;
#define pb push_back
#define pii pair < int , int >
#define F first
#define S second
#define endl '\n'
#define int long long
#define sync ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")

using namespace std;

const int N=2e5+100;
vector <int> g[N];
ll dp[N];
ll p1=0;
ll z=0;

void dfs(ll v, ll p, ll k) {
    multiset <int> s;
    for (auto u : g[v]) {
        if (u == p) continue;
        dfs(u, v, k);
        s.insert(dp[u] + 1);
        if (dp[u] + 1 > k) {
            p1 = 1;
            return;
        }
    }
    if (p1) return;

    vector <int> y;
    while(s.size() > 1) {
        auto t = s.end();
        t--;
        ll val1 = *t;
        s.erase(t);
        if (*s.begin() + val1 > k) {
            y.pb(val1);
            continue;
        }
        t = s.upper_bound(k - val1);
        t--;
        s.erase(t);
        z++;
    }
    if (s.size()) {
        y.pb(*s.begin());
    }
    if (y.size() > 2) {
        p1 = 1;
        return;
    }
    if (y.size()) {
        sort(y.begin(), y.end());
        for (int i = 1; i < y.size(); i++) z++;
        dp[v] = y[0];
        if (v == 1) z++;
    }
    if (dp[1] > k) p1 = 1;
}

pair<int, int> baseline(ll n, vector<pii>& edges) {
    for (int i = 1; i < n; i++) {
        ll u = edges[i-1].F, v = edges[i-1].S;
        g[u].pb(v);
        g[v].pb(u);
    }

    ll l = 0, r = n + 10;
    dfs(1, 1, r);
    ll o = z;

    while(r - l > 1) {
        memset(dp, 0, sizeof dp);
        p1 = 0;
        ll mid = (r + l) / 2;
        z = 0;
        dfs(1, 1, mid);
        if (!p1 && z == o) r = mid;
        else l = mid;
    }

    memset(dp, 0, sizeof dp);
    z = 0;
    p1 = 0;
    dfs(1, 1, r);
    return {z, r};
}

vector<pii> generateInput() {
    ll n = 2e5;
    vector<pii> edges;
    for (int i = 1; i < n; i++) {
        edges.pb({i, i + 1});
    }
    return edges;
}