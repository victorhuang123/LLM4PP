#pragma once

#include <bits/stdc++.h>

using namespace std;

#define MAX 300000

vector<int> g[MAX];

int dfs(int u, int p) {
    int l = 0;
    for (int v : g[u]) {
        if (v != p) {
            l ^= 1 + dfs(v, u);
        }
    }
    return l;
}

int baseline(int n, vector<pair<int, int>>& edges) {
    for (int i = 0; i < n - 1; i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return dfs(1, 0);
}

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        edges.push_back({i, i + 1});
    }
    return edges;
}