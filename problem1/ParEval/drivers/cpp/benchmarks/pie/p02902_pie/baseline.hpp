#pragma once

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> baseline(int n, int m, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> ans;
    vector<int> p(n + 1);
    vector<bool> vis(n + 1);

    auto getCyc = [&](int u, int start) {
        vector<int> tmp;
        while (true) {
            tmp.push_back(u);
            if (u == start) break;
            u = p[u];
        }
        reverse(tmp.begin(), tmp.end());
        ans.push_back(tmp);
    };

    auto bfs = [&](int u, int start) {
        fill(vis.begin(), vis.end(), false);
        queue<int> q;
        p[u] = u;
        vis[u] = true;
        q.push(u);

        while (!q.empty()) {
            u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (v == start) {
                    getCyc(u, start);
                    return;
                }
            }

            for (int v : adj[u]) {
                if (vis[v]) continue;
                vis[v] = true;
                p[v] = u;
                q.push(v);
            }
        }
    };

    for (int i = 0; i < m; i++) {
        int u = edges[i].first, v = edges[i].second;
        adj[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        bfs(i, i);
    }

    return ans;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u = rand() % n + 1;
        int v = rand() % n + 1;
        edges.push_back({u, v});
    }
    return edges;
}