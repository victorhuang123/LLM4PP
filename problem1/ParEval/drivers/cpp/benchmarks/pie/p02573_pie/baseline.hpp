#pragma once

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int baseline(int n, int m, vector<pair<int, int>>& edges) {
    vector<bool> seen(n, false);
    vector<set<int>> graph(n);

    for (int i = 0; i < m; i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        a--; b--;
        graph[a].insert(b);
        graph[b].insert(a);
    }

    auto surch = [&](const set<int>& g, auto&& surch) -> int {
        int succ = 0;
        for (auto x : g) {
            if (seen[x]) continue;
            seen[x] = true;
            succ++;
            succ += surch(graph[x], surch);
        }
        return succ;
    };

    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        int tmp = surch(graph[i], surch);
        ans = max(ans, tmp);
    }

    return ans;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        edges.push_back({a, b});
    }
    return edges;
}