#pragma once

#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

#define INFTY (1<<21)

int baseline(int n, int m, const vector<vector<int>>& G, const vector<int>& E) {
    auto eprim = [&](int base) {
        vector<int> d(n, INFTY);
        vector<bool> visited(n, false);
        d[0] = 0;
        int cnt = 0;
        int ans = 0;

        while (true) {
            int minv = INFTY;
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && minv > d[i]) {
                    minv = d[i];
                    u = i;
                }
            }
            if (minv == INFTY) break;
            if (u != 0 && ans < minv) ans = minv;
            cnt++;
            visited[u] = true;

            for (int v = 0; v < n; v++) {
                if (visited[v] || G[u][v] == INFTY) continue;
                if (base > G[u][v]) continue;
                if (d[v] > G[u][v] - base) {
                    d[v] = G[u][v] - base;
                }
            }
        }
        if (cnt != n) return INFTY;
        return ans;
    };

    int minv = INFTY;
    for (int i = 0; i < m; i++) {
        minv = min(minv, eprim(E[i]));
    }
    return minv == INFTY ? -1 : minv;
}

vector<vector<int>> generateInput(int n) {
    vector<vector<int>> G(n, vector<int>(n, INFTY));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            G[i][j] = rand() % 1000 + 1;
        }
    }
    return G;
}

vector<int> generateE(int m) {
    vector<int> E(m);
    for (int i = 0; i < m; i++) {
        E[i] = rand() % 1000 + 1;
    }
    return E;
}