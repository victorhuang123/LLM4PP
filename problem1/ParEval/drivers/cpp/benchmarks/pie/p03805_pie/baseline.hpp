#pragma once

#include<vector>
#include<algorithm>
#include<cstring>
#include<functional>

using namespace std;

int baseline(int n, int m, vector<pair<int, int>>& edges) {
    vector<vector<int>> g(n + 1);
    vector<int> vis(n + 1, 0);
    int num = 0;

    for (int i = 0; i < m; i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    function<void(int)> dfs = [&](int t) {
        int j;
        for (j = 1; j <= n; j++) {
            if (vis[j] != 1)
                break;
        }
        if (j == n + 1) {
            num++;
            return;
        }
        for (int i = 0; i < g[t].size(); i++) {
            int x = g[t][i];
            if (vis[x] == 0) {
                vis[x] = 1;
                dfs(x);
                vis[x] = 0;
            }
        }
    };

    vis[1] = 1;
    for (int i = 0; i < g[1].size(); i++) {
        int x = g[1][i];
        vis[x] = 1;
        dfs(x);
        vis[x] = 0;
    }

    return num;
}

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        edges.push_back({i, i + 1});
    }
    edges.push_back({n, 1});
    return edges;
}