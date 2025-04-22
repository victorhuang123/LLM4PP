#pragma once

#include <vector>
#include <queue>

using namespace std;

long long baseline(int n, vector<int>& parent) {
    vector<vector<int>> tree(n + 1);
    vector<vector<int>> query(n + 1);
    vector<int> father(n + 1);
    vector<int> depth(n + 1);
    long long ans = 0;

    auto findSet = [&](int x) {
        if (x == father[x])
            return x;
        else
            return father[x] = findSet(father[x]);
    };

    auto unionSet = [&](int x, int y) {
        int fx = findSet(x);
        int fy = findSet(y);
        if (fy == fx)
            return;
        father[fy] = fx;
    };

    auto bfs = [&]() {
        queue<int> Q;
        Q.push(1);
        int last = 0;
        int t;
        while (!Q.empty()) {
            t = Q.front();
            if (last != 0) {
                query[last].push_back(t);
            }
            last = t;
            Q.pop();
            for (unsigned int i = 0; i < tree[t].size(); ++i) {
                Q.push(tree[t][i]);
            }
        }
    };

    auto Tarjan_LCA = [&](int u) {
        father[u] = u;
        int t;
        for (unsigned int i = 0; i < tree[u].size(); ++i) {
            t = tree[u][i];
            depth[t] = depth[u] + 1;
            Tarjan_LCA(t);
            unionSet(u, t);
        }
        for (unsigned int i = 0; i < query[u].size(); ++i) {
            t = query[u][i];
            if (father[t] != 0) {
                ans += (long long)depth[u] + (long long)depth[t] - 2 * (long long)depth[findSet(t)];
            } else {
                query[t].push_back(u);
            }
        }
    };

    for (int i = 2; i <= n; ++i) {
        tree[parent[i]].push_back(i);
    }
    bfs();
    Tarjan_LCA(1);
    return ans;
}

vector<int> generateInput(int n) {
    vector<int> parent(n + 1);
    for (int i = 2; i <= n; ++i) {
        parent[i] = i / 2;
    }
    return parent;
}