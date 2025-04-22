#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(a) ((int)(a).size())

const int N = 100005;

int baseline(int n1, int n2, vector<vector<int>>& g, vector<int>& m1, vector<int>& m2, vector<bool>& in_vc1, vector<bool>& in_vc2) {
    vector<bool> vis(N);
    REP(i, n1) m1[i] = -1;
    REP(i, n2) m2[i] = -1;
    bool changed;
    auto dfs = [&](int u, auto&& dfs) -> bool {
        if (u < 0) return true;
        if (vis[u]) return false; else vis[u] = true;
        for(int v : g[u])
            if (dfs(m2[v], dfs)) { m1[u] = v; m2[v] = u; return true; }
        return false;
    };
    do {
        changed = 0;
        REP(i, n1) vis[i] = false;
        REP(i, n1) if (m1[i] < 0) changed |= dfs(i, dfs);
    } while(changed);
    REP(i, n1) if (m1[i] != -1) {
        if (vis[i]) in_vc2[m1[i]] = true;
        else in_vc1[i] = true;
    }
    int siz = 0;
    REP(i, n1) siz += (m1[i] != -1);
    return siz;
}

vector<vector<int>> generateInput(int n1, int n2) {
    vector<vector<int>> g(n1);
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            if (rand() % 2) {
                g[i].push_back(j);
            }
        }
    }
    return g;
}