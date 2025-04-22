#pragma once

#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> generateInput() {
    int n = 200000;
    int m = 200000;
    vector<pair<int, int>> edges;
    for (int i = 1; i <= m; i++) {
        edges.push_back({i, i + 1});
    }
    return edges;
}

bool baseline(int n, int m, vector<pair<int, int>>& edges) {
    vector<int> p[200010];
    int flag = 0;

    for (int i = 0; i < m; i++) {
        int x = edges[i].first;
        int y = edges[i].second;
        p[x].push_back(y);
        p[y].push_back(x);
    }

    for (int i = 0; i < p[1].size(); i++) {
        int k = p[1][i];
        for (int j = 0; j < p[k].size(); j++) {
            if (p[k][j] == n) {
                flag = 1;
                break;
            }
        }
    }

    return flag;
}