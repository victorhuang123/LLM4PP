#pragma once

#include <vector>
#include <algorithm>

using namespace std;

vector<int> baseline(int n, int m, vector<pair<int, int>>& edges) {
    const int MAX = 1000 * 100 + 47;
    vector<int> V;
    vector<int> g[MAX];
    int U[MAX] = {0};

    for (int i = 0; i < m; i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto dfs = [&](int v, auto&& dfs) -> void {
        U[v] = 1;
        V.push_back(v);
        for (int i = 0; i < g[v].size(); i++) {
            int to = g[v][i];
            if (U[to]) continue;
            dfs(to, dfs);
            break;
        }
    };

    U[0] = 1;
    V.push_back(0);
    dfs(g[0][0], dfs);
    reverse(V.begin(), V.end());

    for (int i = 0; i < g[0].size(); i++) {
        int to = g[0][i];
        if (U[to]) continue;
        dfs(to, dfs);
        break;
    }

    return V;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        edges.push_back({a, b});
    }
    return edges;
}