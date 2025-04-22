#pragma once

#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

const int maxN = 100001;
bool used[maxN];

pair<int, int> dfs(int v, const vector<pair<int, int>> g[]) {
    used[v] = true;

    pair<int, int> ret = make_pair(0, v);
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i].first;
        int w = g[v][i].second;
        if (used[u]) continue;
        pair<int, int> tmp = dfs(u, g);
        ret = max(ret, make_pair(w + tmp.first, tmp.second));
    }
    return ret;
}

int baseline(int n, const vector<tuple<int, int, int>>& edges) {
    vector<pair<int, int>> g[maxN];
    for (const auto& edge : edges) {
        int a = get<0>(edge);
        int b = get<1>(edge);
        int c = get<2>(edge);
        g[a].push_back(make_pair(b, c));
        g[b].push_back(make_pair(a, c));
    }

    int v = dfs(0, g).second;
    for (int i = 0; i < n; ++i) used[i] = false;
    return dfs(v, g).first;
}

vector<tuple<int, int, int>> generateInput() {
    int n = 100000;
    vector<tuple<int, int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back(make_tuple(i - 1, i, 1));
    }
    return edges;
}