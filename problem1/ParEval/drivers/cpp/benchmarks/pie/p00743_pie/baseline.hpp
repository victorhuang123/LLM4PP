#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

double baseline(int n, int m, int s, int g, vector<vector<int>>& edges) {
    vector<vector<pair<int, pair<int, int>>>> G(n);
    vector<vector<vector<double>>> dist(n, vector<vector<double>>(n, vector<double>(33, 1e9)));
    dist[s][0][0] = 0;

    for (int i = 0; i < m; ++i) {
        int x = edges[i][0], y = edges[i][1], d = edges[i][2], c = edges[i][3];
        G[x].push_back({y, {d, c}});
        G[y].push_back({x, {d, c}});
    }

    priority_queue<pair<pair<double, int>, pair<int, int>>, vector<pair<pair<double, int>, pair<int, int>>>, greater<pair<pair<double, int>, pair<int, int>>>> que;
    que.push({{0, s}, {0, 0}});

    while (!que.empty()) {
        auto pp = que.top(); que.pop();
        int v = pp.first.second;
        int prev = pp.second.first;
        int u = pp.second.second;

        if (dist[v][prev][u] < pp.first.first) continue;

        for (auto& e : G[v]) {
            int to = e.first;
            int cost = e.second.first;
            int ub = e.second.second;

            if (to == prev) continue;

            for (int j = -1; j <= 1; ++j) {
                int new_u = u + j;
                if (new_u <= 0 || new_u > ub) continue;

                double new_dist = dist[v][prev][u] + (1.0 * cost / new_u);
                if (dist[to][v][new_u] > new_dist) {
                    dist[to][v][new_u] = new_dist;
                    que.push({{new_dist, to}, {v, new_u}});
                }
            }
        }
    }

    double ans = 1e9;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dist[g][i][1]);
    }

    return ans;
}

vector<vector<int>> generateInput(int n, int m) {
    vector<vector<int>> edges(m, vector<int>(4));
    for (int i = 0; i < m; ++i) {
        edges[i][0] = rand() % n;
        edges[i][1] = rand() % n;
        edges[i][2] = rand() % 100 + 1;
        edges[i][3] = rand() % 30 + 1;
    }
    return edges;
}