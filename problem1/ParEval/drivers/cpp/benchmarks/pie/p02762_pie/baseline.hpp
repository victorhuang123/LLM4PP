#pragma once

#include <vector>
#include <queue>

using namespace std;

vector<int> baseline(int n, int m, int k, vector<pair<int, int>>& edges, vector<pair<int, int>>& queries) {
    queue<int> Q;
    vector<vector<int>> v(n + 1), p(n + 1);
    vector<int> parent(n + 1), visit(n + 1), group(n + 1);
    vector<int> result(n);

    auto bfs = [&](int start) {
        Q.push(start);
        visit[start] = 1;
        parent[start] = start;
        while (!Q.empty()) {
            int t = Q.front(); Q.pop();
            for (int next : p[t]) {
                if (!visit[next]) {
                    parent[next] = start;
                    visit[next] = 1;
                    Q.push(next);
                }
            }
        }
    };

    for (auto& edge : edges) {
        int a = edge.first, b = edge.second;
        v[a].push_back(b);
        v[b].push_back(a);
        p[a].push_back(b);
        p[b].push_back(a);
    }

    for (auto& query : queries) {
        int c = query.first, d = query.second;
        v[c].push_back(d);
        v[d].push_back(c);
    }

    for (int i = 1; i <= n; i++) {
        if (!visit[i]) {
            bfs(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        group[parent[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        int cnt = group[parent[i]];
        for (int neighbor : v[i]) {
            if (parent[neighbor] == parent[i]) {
                --cnt;
            }
        }
        result[i - 1] = cnt - 1;
    }

    return result;
}

vector<pair<int, int>> generateInput(int n, int m, int k) {
    vector<pair<int, int>> edges;
    vector<pair<int, int>> queries;
    for (int i = 0; i < m; i++) {
        edges.push_back({rand() % n + 1, rand() % n + 1});
    }
    for (int i = 0; i < k; i++) {
        queries.push_back({rand() % n + 1, rand() % n + 1});
    }
    return edges, queries;
}