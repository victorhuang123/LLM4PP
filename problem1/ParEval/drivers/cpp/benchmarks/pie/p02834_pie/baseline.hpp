#pragma once

#include<bits/stdc++.h>
using namespace std;

vector<int> generate_input(int N) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < N; i++) {
        edges.push_back({i, i + 1});
    }
    return edges;
}

int baseline(int N, int u, int v, vector<pair<int, int>>& edges) {
    vector<vector<int>> E(N + 1);
    vector<int> DT(N + 1, 0), DA(N + 1, 0);

    for (auto& edge : edges) {
        int a = edge.first;
        int b = edge.second;
        E[a].push_back(b);
        E[b].push_back(a);
    }

    function<void(int, int, vector<int>&)> dfs = [&](int A, int d, vector<int>& D) {
        if (D[A]) return;
        D[A] = d;
        for (int to : E[A]) {
            dfs(to, d + 1, D);
        }
    };

    dfs(u, 1, DT);
    dfs(v, 1, DA);

    int saidai = -1;
    for (int i = 1; i <= N; i++) {
        if (DT[i] < DA[i]) saidai = max(saidai, DA[i]);
    }

    return max(0, saidai - 2);
}