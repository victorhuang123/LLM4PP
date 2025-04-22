#pragma once

#include <vector>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

vector<int> baseline(int V, int E, vector<pair<int, int>>& edges, int Q, vector<pair<int, int>>& queries) {
    vector<vector<int>> G1(V), G2(V);
    vector<bool> visit1(V, false), visit2(V, false);
    vector<int> Ans(V);
    vector<int> prenum(V);
    int timer = 0;

    for (int i = 0; i < E; i++) {
        int s = edges[i].first, t = edges[i].second;
        G1[s].emplace_back(t);
        G2[t].emplace_back(s);
    }

    auto dfs1 = [&](int u, auto&& dfs1) -> void {
        visit1[u] = true;
        for (int v : G1[u]) {
            if (visit1[v] == false) {
                dfs1(v, dfs1);
            }
        }
        prenum[timer++] = u;
    };

    auto dfs2 = [&](int u, auto&& dfs2) -> void {
        visit2[u] = true;
        Ans[u] = timer;
        for (int v : G2[u]) {
            if (visit2[v] == false) {
                dfs2(v, dfs2);
            }
        }
    };

    for (int i = 0; i < V; i++) {
        if (visit1[i] == false) {
            dfs1(i, dfs1);
        }
    }

    timer = 0;
    for (int i = V - 1; i >= 0; i--) {
        if (visit2[prenum[i]] == false) {
            dfs2(prenum[i], dfs2);
            timer++;
        }
    }

    vector<int> result(Q);
    for (int i = 0; i < Q; i++) {
        int u = queries[i].first, v = queries[i].second;
        result[i] = (Ans[u] == Ans[v]) ? 1 : 0;
    }

    return result;
}

vector<pair<int, int>> generateInput(int V, int E, int Q) {
    vector<pair<int, int>> edges(E);
    vector<pair<int, int>> queries(Q);

    for (int i = 0; i < E; i++) {
        edges[i] = {rand() % V, rand() % V};
    }

    for (int i = 0; i < Q; i++) {
        queries[i] = {rand() % V, rand() % V};
    }

    return edges;
}