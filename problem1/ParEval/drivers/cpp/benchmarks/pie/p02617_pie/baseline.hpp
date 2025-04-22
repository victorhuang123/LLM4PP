#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        int u = i;
        int v = i + 1;
        edges.push_back({u, v});
    }
    return edges;
}

long long baseline(int n, const vector<pair<int, int>>& edges) {
    long long ans = 1LL * n * (n + 1) * (n + 2) / 6;

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        if (u > v) swap(u, v);
        ans -= 1LL * u * (n - v + 1);
    }

    return ans;
}