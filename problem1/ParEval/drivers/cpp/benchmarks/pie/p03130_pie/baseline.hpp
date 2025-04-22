#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> generateInput() {
    vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}};
    return edges;
}

bool baseline(const vector<vector<int>>& edges) {
    const int N = 3e5 + 7;
    int cnt = 0;
    vector<bool> used(N, false);
    vector<vector<int>> v(N);

    for (const auto& edge : edges) {
        int x = edge[0];
        int y = edge[1];
        v[x].push_back(y);
        v[y].push_back(x);
    }

    function<void(int)> dfs = [&](int x) {
        if (used[x]) {
            return;
        }
        used[x] = true;
        cnt++;
        if (cnt == 4) {
            return;
        }
        for (int y : v[x]) {
            dfs(y);
        }
        cnt--;
    };

    for (int i = 1; i <= 4; i++) {
        cnt = 0;
        dfs(i);
        if (cnt == 4) {
            return true;
        }
        fill(used.begin(), used.end(), false);
    }
    return false;
}