#pragma once

#include <vector>
#include <utility>

using namespace std;

int baseline(int n, vector<pair<int, int>> edges) {
    vector<vector<int>> g(n + 1);
    for (auto edge : edges) {
        int x = edge.first, y = edge.second;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int r = 0, st = 0;

    auto dfs = [&](int v, int pr, int lvl, auto&& dfs) -> void {
        if (r < lvl) {
            r = lvl;
            st = v;
        }
        for (auto to : g[v]) {
            if (to != pr) {
                dfs(to, v, lvl + 1, dfs);
            }
        }
    };

    dfs(1, 0, 0, dfs);
    r = 0;
    dfs(st, 0, 0, dfs);

    return (r % 3 == 1) ? 2 : 1;
}

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i - 1, i});
    }
    return edges;
}