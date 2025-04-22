#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 200005, maxm = 200005;

struct edge {
    int to, next, vis;
};

vector<int> baseline(int n, int m, const vector<int>& d, const vector<pair<int, int>>& edges) {
    vector<edge> e(maxm * 2);
    vector<int> h(maxn, 0), w(maxm, 1e9), col(maxn, -1), fa(maxn, 0), fe(maxn, 0);
    int tot = 1;

    auto add = [&](int u, int v) {
        e[++tot] = {v, h[u], 0}; h[u] = tot;
        e[++tot] = {u, h[v], 0}; h[v] = tot;
    };

    for (const auto& edge : edges) {
        add(edge.first, edge.second);
    }

    auto dfs = [&](int u, auto&& dfs) -> void {
        for (int i = h[u]; i; i = e[i].next) {
            if (!e[i].vis) continue;
            int v = e[i].to;
            if (col[v] == -1) {
                col[v] = 1 - col[u];
                dfs(v, dfs);
            }
        }
    };

    for (int u = 1; u <= n; ++u) {
        if (!h[u]) return {-1};
        int p = h[u];
        for (int i = e[p].next; i; i = e[i].next) {
            if (d[e[i].to] < d[e[p].to]) p = i;
            else if (d[e[i].to] == d[e[p].to] && e[i].to < e[p].to) p = i;
        }
        if (d[e[p].to] > d[u]) return {-1};
        w[p >> 1] = d[u]; fa[u] = e[p].to; e[p ^ 1].vis = 1;
    }

    fill(col.begin() + 1, col.begin() + n + 1, -1);
    for (int i = 1; i <= n; ++i) {
        if (fa[fa[i]] == i && col[i] == -1) {
            col[i] = 0;
            dfs(i, dfs);
        }
    }

    vector<int> result;
    for (int i = 1; i <= n; ++i) {
        result.push_back(col[i] == 0 ? 'B' : 'W');
    }
    for (int i = 1; i <= m; ++i) {
        result.push_back(w[i]);
    }

    return result;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        edges.push_back({rand() % n + 1, rand() % n + 1});
    }
    return edges;
}