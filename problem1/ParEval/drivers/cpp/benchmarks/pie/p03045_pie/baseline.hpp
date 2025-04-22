#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> generateInput(int n, int m) {
    vector<int> x(m + 1), y(m + 1), z(m + 1);
    for (int i = 1; i <= m; i++) {
        x[i] = rand() % n + 1;
        y[i] = rand() % n + 1;
        z[i] = rand() % 100;
    }
    return {x, y, z};
}

int baseline(int n, int m, vector<int>& x, vector<int>& y, vector<int>& z) {
    vector<vector<int>> g(n + 1);
    vector<bool> used(n + 1, false);
    int ans = 0;

    auto dfs = [&](int v, auto&& dfs) -> void {
        used[v] = true;
        for (auto to : g[v])
            if (!used[to])
                dfs(to, dfs);
    };

    for (int i = 1; i <= m; i++) {
        g[x[i]].push_back(y[i]);
        g[y[i]].push_back(x[i]);
    }

    for (int i = 1; i <= n; i++)
        if (!used[i])
            dfs(i, dfs), ans++;

    return ans;
}