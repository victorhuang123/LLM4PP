#pragma once

#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

LL C(int x) {
    return (LL)x * (x - 1) / 2;
}

int dfs(int x, vector<vector<int>>& adj, vector<bool>& visited) {
    if (visited[x]) return 0;
    visited[x] = true;
    int ret = 1;
    for (int i = 0; i < adj[x].size(); ++i) {
        ret += dfs(adj[x][i], adj, visited);
    }
    return ret;
}

LL baseline(int n, int m, vector<pii>& edges) {
    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);
    
    for (int i = 0; i < m; ++i) {
        int a = edges[i].first;
        int b = edges[i].second;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    int a = dfs(1, adj, visited);
    int b = dfs(2, adj, visited);
    
    if (a < b) swap(a, b);
    LL risan = C(n - b) + C(b) - m;
    return risan;
}

vector<pii> generateInput(int n, int m) {
    vector<pii> edges(m);
    for (int i = 0; i < m; ++i) {
        edges[i] = {i + 1, (i + 1) % n + 1};
    }
    return edges;
}