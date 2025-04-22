#pragma once

#include <vector>
#include <utility>

using namespace std;

bool baseline(int n, int u, int v, const vector<pair<int, int>>& edges) {
    if (n % 2) return false;
    
    vector<vector<int>> g(n);
    vector<int> sz(n, 0);
    vector<int> rt(n, -1);
    
    for (int i = 0; i < n - 1; i++) {
        int a = edges[i].first - 1, b = edges[i].second - 1;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    auto dfs = [&](int p, int b, auto&& dfs) -> void {
        sz[p] = 1;
        rt[p] = b;
        for (int d : g[p]) {
            if (d == b) continue;
            dfs(d, p, dfs);
            sz[p] += sz[d];
        }
    };
    
    dfs(u - 1, -1, dfs);
    
    int st = v - 1;
    while (true) {
        if (sz[st] > n / 2) {
            return false;
        }
        if (sz[st] == n / 2) {
            break;
        }
        st = rt[st];
    }
    
    vector<vector<int>> g2(n);
    for (int i = 0; i < n - 1; i++) {
        int a = edges[i].first - 1, b = edges[i].second - 1;
        if (rt[b] == a) swap(a, b);
        if (a == st) continue;
        g2[a].push_back(b);
        g2[b].push_back(a);
    }
    
    auto ispath = [&](int s) -> bool {
        if (g2[s].size() >= 2) return false;
        if (g2[s].size() == 0) return true;
        int b = -1;
        int p = s;
        while (true) {
            for (int d : g2[p]) {
                if (d == b) continue;
                b = p;
                p = d;
                break;
            }
            if (g2[p].size() == 1) return true;
            if (g2[p].size() > 2) return false;
        }
    };
    
    return (ispath(u - 1) && ispath(v - 1));
}

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        edges.push_back({i, i + 1});
    }
    return edges;
}