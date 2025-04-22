#pragma once

#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

ll baseline(int n, int m, vector<vector<ll>>& edges) {
    ll adj[100 + 30][100 + 30];
    int f[100 + 30], bestf[100 + 30];
    int v[100 + 30];
    ll w[100 + 30];
    bool a[100 + 30];
    ll ans = 0;

    memset(adj, 0, sizeof(adj));
    for (int i = 0; i < m; ++i) {
        int a = edges[i][0], b = edges[i][1];
        ll c = edges[i][2];
        if (c < 0) {
            ans += c;
        } else {
            adj[a][b] = adj[b][a] = adj[a][b] + c;
        }
    }

    for (int i = 0; i < n; ++i) {
        f[i] = v[i] = i;
    }

    ll mincut_ans = (-1ull) >> 1;
    for (int t = n; t > 1; --t) {
        a[0] = true;
        for (int i = 1; i < t; ++i) {
            a[i] = false;
            w[i] = adj[v[0]][v[i]];
        }
        int prev = v[0];
        for (int i = 1; i < t; ++i) {
            int zj = -1;
            for (int j = 1; j < t; ++j) {
                if (a[j] == false && (zj == -1 || w[j] > w[zj])) {
                    zj = j;
                }
            }
            a[zj] = true;
            if (i == t - 1) {
                if (w[zj] < mincut_ans) {
                    mincut_ans = w[zj];
                    copy(f, f + n, bestf);
                }
                for (int k = 0; k < t; ++k) {
                    adj[v[k]][prev] = adj[prev][v[k]] += adj[v[zj]][v[k]];
                }
                f[v[zj]] = prev;
                v[zj] = v[t - 1];
                break;
            }
            prev = v[zj];
            for (int j = 1; j < t; ++j) {
                if (a[j] == false) {
                    w[j] += adj[v[zj]][v[j]];
                }
            }
        }
    }

    return ans + mincut_ans;
}

vector<vector<ll>> generateInput(int n, int m) {
    vector<vector<ll>> edges(m, vector<ll>(3));
    for (int i = 0; i < m; ++i) {
        edges[i][0] = rand() % n;
        edges[i][1] = rand() % n;
        edges[i][2] = rand() % 1000000 - 500000;
    }
    return edges;
}