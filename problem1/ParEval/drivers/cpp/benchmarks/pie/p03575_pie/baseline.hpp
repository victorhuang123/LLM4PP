#pragma once

#include <vector>
#include <cstring>

using namespace std;

const int maxn = 1000 + 10;

vector<int> da[200];
int d1[100], d2[100];
int vis[100];

int dfs(int s, int d, int a, int b) {
    if (s == d) {
        return 1;
    }

    vis[s] = 1;
    int mm = da[s].size();
    for (int i = 0; i < mm; i++) {
        int v = da[s][i];
        if ((s == a && v == b) || (s == b && v == a))
            continue;
        if (!vis[v]) {
            if (dfs(v, d, a, b) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

int baseline(int n, int m, vector<pair<int, int>>& edges) {
    int ans = 0;
    int f;

    for (int i = 0; i < m; i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        d1[i] = a;
        d2[i] = b;
        da[b].push_back(a);
        da[a].push_back(b);
    }

    for (int i = 0; i < m; i++) {
        int a = d1[i];
        int b = d2[i];
        f = 0;

        for (int s = 1; s <= n; s++) {
            for (int d = 1; d <= n; d++) {
                memset(vis, 0, sizeof(vis));
                if (dfs(s, d, a, b) == 0) {
                    ans++;
                    f = 1;
                    break;
                }
            }
            if (f)
                break;
        }
    }

    return ans;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        edges.push_back({rand() % n + 1, rand() % n + 1});
    }
    return edges;
}