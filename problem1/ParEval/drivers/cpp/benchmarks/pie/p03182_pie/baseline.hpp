#pragma once

#include <bits/stdc++.h>

#define int long long

using namespace std;

typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;

const int inf = 1e9, mod = 1e9 + 7;
const int INF = 1e18;

int baseline(int n, int m, vector<tuple<int, int, int>>& queries) {
    vector<int> t(n << 2, 0), add(n << 2, 0), dp(n + 1, 0);
    vector<vpii> gg(n + 2);
    vector<vi> g(n + 1);

    auto push = [&](int v) {
        if (add[v]) {
            add[v << 1] += add[v];
            add[v << 1 | 1] += add[v];
            t[v << 1] += add[v];
            t[v << 1 | 1] += add[v];
            add[v] = 0;
        }
    };

    auto update = [&](int l, int r, int x, int v = 1, int tl = 0, int tr = n) {
        if (l > r || l > tr || tl > r) 
            return;

        if (l <= tl && tr <= r) {
            t[v] += x;
            add[v] += x;
            return;
        }

        push(v);
        int tm = (tl + tr) >> 1;
        update(l, r, x, v << 1, tl, tm);
        update(l, r, x, v << 1 | 1, tm + 1, tr);
        t[v] = max(t[v << 1], t[v << 1 | 1]);
    };

    auto get = [&](int l, int r, int v = 1, int tl = 0, int tr = n) {
        if (l > r || tl > r || l > tr)
            return -INF;

        if (l <= tl && tr <= r) 
            return t[v]; 

        push(v);
        int tm = (tl + tr) >> 1;
        return max(get(l, r, v << 1, tl, tm), get(l, r, v << 1 | 1, tm + 1, tr));
    };

    for (auto& [l, r, x] : queries) {
        g[l].push_back(x);        
        gg[r + 1].push_back({l, x});
    }

    for (int i = 1; i <= n; i++) {
        for (auto x : g[i]) 
            update(0, i - 1, x); 

        for (auto x : gg[i]) 
            update(0, x.first - 1, -x.second); 

        dp[i] = get(0, i - 1);            
        update(i, i, dp[i]);                    
    }

    return dp[n];
}

vector<tuple<int, int, int>> generateInput(int n, int m) {
    vector<tuple<int, int, int>> queries(m);
    for (int i = 0; i < m; i++) {
        int l = rand() % n + 1;
        int r = rand() % n + 1;
        if (l > r) swap(l, r);
        int x = rand() % 1000000 + 1;
        queries[i] = {l, r, x};
    }
    return queries;
}