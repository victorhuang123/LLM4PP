#pragma once

#include <vector>
#include <cstring>

using namespace std;

const int maxn = 200005;

struct Query {
    int v, d, c;
};

vector<int> baseline(int n, int m, int Q, vector<pair<int, int>>& edges, vector<Query>& queries) {
    vector<int> G[maxn];
    bool vis[maxn][15];
    int color[maxn];

    memset(color, 0, sizeof(color));
    memset(vis, false, sizeof(vis));

    for (int i = 0; i < m; i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    auto solve = [&](int v, int d, int c) {
        if (vis[v][d]) return;
        if (color[v] == 0) color[v] = c;
        if (d <= 0) return;

        for (int i = 0; i < G[v].size(); i++) {
            solve(G[v][i], d - 1, c);
        }
        vis[v][d] = 1;
    };

    for (int i = Q - 1; i >= 0; i--) {
        solve(queries[i].v, queries[i].d, queries[i].c);
    }

    vector<int> result;
    for (int i = 1; i <= n; i++) {
        result.push_back(color[i]);
    }

    return result;
}

vector<pair<int, int>> generateEdges(int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        edges.push_back({i + 1, (i + 2) % m + 1});
    }
    return edges;
}

vector<Query> generateQueries(int Q) {
    vector<Query> queries;
    for (int i = 0; i < Q; i++) {
        queries.push_back({i + 1, 10, i + 1});
    }
    return queries;
}