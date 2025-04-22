#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define F first

#define S second

#define pii pair<int, int>

#define eb emplace_back

#define all(v) v.begin(), v.end()

#define rep(i, n) for (int i = 0; i < (n); ++i)

#define rep3(i, l, n) for (int i = l; i < (n); ++i)

#define sz(v) (int)v.size()

#define inf (int)(1e9+7)

#define INF (ll)(1e18)

#define abs(x) (x >= 0 ? x : -(x))

#define ceil(a, b) a / b + !!(a % b)

template<typename T1, typename T2> inline bool chmin(T1 &a, T2 b) { if (a > b) { a = b; return 1; } return 0; }

template<typename T1, typename T2> inline bool chmax(T1 &a, T2 b) { if (a < b) { a = b; return 1; } return 0; }

template<typename T> T gcd(T a, T b) { if (b == 0) return a; return gcd(b, a % b); }

vector<int> baseline(int n, vector<tuple<int, int, int>>& edges) {
    vector<int> col(n, -1);
    vector<vector<pii>> g(n);

    rep(i, n - 1) {
        int u, v, w;
        tie(u, v, w) = edges[i];
        u--; v--;
        g[u].eb(pii(v, w));
        g[v].eb(pii(u, w));
    }

    function<void(int)> dfs = [&](int now) {
        for (pii nxt : g[now]) {
            if (col[nxt.F] == -1) {
                col[nxt.F] = col[now] ^ (nxt.S % 2);
                dfs(nxt.F);
            }
        }
    };

    col[0] = 0;
    dfs(0);
    return col;
}

vector<tuple<int, int, int>> generateInput(int n) {
    vector<tuple<int, int, int>> edges;
    rep(i, n - 1) {
        int u = i + 1;
        int v = i + 2;
        int w = rand() % 100 + 1;
        edges.eb(u, v, w);
    }
    return edges;
}