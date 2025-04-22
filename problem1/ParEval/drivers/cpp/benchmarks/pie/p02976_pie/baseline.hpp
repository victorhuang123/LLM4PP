#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        edges.push_back({a, b});
    }
    return edges;
}

vector<pair<int, int>> baseline(int n, int m, vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n + 1), adjexit(n + 1);
    vector<bool> vis(n + 1, false);
    vector<int> dis(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int a = edges[i].first, b = edges[i].second;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if (m % 2) {
        return {{-1, -1}};
    }

    function<void(int)> dfs = [&](int v) {
        vis[v] = true;
        for (int u : adj[v]) {
            if (!vis[u]) {
                dis[u] = dis[v] + 1;
                dfs(u);
                adjexit[u].size() % 2 ? adjexit[u].push_back(v) : adjexit[v].push_back(u);
            } else if (dis[v] < dis[u]) {
                adjexit[v].push_back(u);
            }
        }
    };

    dfs(1);

    vector<pair<int, int>> result;
    for (int i = 1; i <= n; i++) {
        for (int j : adjexit[i]) {
            result.push_back({i, j});
        }
    }
    return result;
}