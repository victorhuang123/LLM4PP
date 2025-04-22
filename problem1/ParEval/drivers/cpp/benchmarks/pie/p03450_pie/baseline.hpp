#pragma once

#include <bits/stdc++.h>

#define LL long long
#define mp make_pair
#define pb push_back
#define INF (1<<29)

using namespace std;

typedef pair<int,int>pii;

bool baseline(int n, int m, vector<tuple<int, int, int>>& edges) {
    vector<pii>G[200010];
    int col[200010];
    int vis[200010];
    memset(vis, -1, sizeof(vis));

    if (m == 0) {
        return true;
    }

    for (auto& edge : edges) {
        int l = get<0>(edge);
        int r = get<1>(edge);
        int d = get<2>(edge);
        G[l].pb(mp(r, d));
        G[r].pb(mp(l, -d));
    }

    function<bool(int, int)> dfs = [&](int x, int co) {
        if (vis[x] != -1) return col[x] == co;
        vis[x] = 1;
        col[x] = co;
        for (pii i : G[x]) {
            if (dfs(i.first, co + i.second) == 0) return false;
        }
        return true;
    };

    for (int i = 1; i <= n; i++) {
        if (vis[i] != -1) continue;
        memset(col, 0, sizeof(col));
        if (dfs(i, 0) == 0) {
            return false;
        }
    }
    return true;
}

vector<tuple<int, int, int>> generateInput(int n, int m) {
    vector<tuple<int, int, int>> edges;
    for (int i = 1; i <= m; i++) {
        int u = i;
        int v = (i % n) + 1;
        int w = 1;
        edges.pb(make_tuple(u, v, w));
    }
    return edges;
}