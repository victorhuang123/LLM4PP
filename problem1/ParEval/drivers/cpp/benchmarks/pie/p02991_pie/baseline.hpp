#pragma once

#include <bits/stdc++.h>

using namespace std;

static const int MAX = 300000;
static const int INF = 1e9;

int baseline(int n, int m, vector<pair<int, int>>& edges, int s, int t) {
    vector<int> G[MAX], d(MAX, INF);

    for (int i = 0; i < m; i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        u--;
        v--;
        G[u].emplace_back(v + 100000);
        G[u + 100000].emplace_back(v + 200000);
        G[u + 200000].emplace_back(v);
    }

    queue<int> q;
    q.push(s);
    d[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < G[u].size(); v++) {
            if (d[G[u][v]] == INF) {
                d[G[u][v]] = d[u] + 1;
                q.push(G[u][v]);
            }
        }
    }

    if (d[t] == INF) return -1;
    else return d[t] / 3;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u = rand() % n + 1;
        int v = rand() % n + 1;
        edges.emplace_back(u, v);
    }
    return edges;
}