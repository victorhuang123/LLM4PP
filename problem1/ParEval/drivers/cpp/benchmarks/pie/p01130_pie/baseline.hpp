#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int baseline(int n, int m, int s, int g1, int g2, const vector<vector<int>>& edges) {
    vector<vector<int>> adj(n, vector<int>(n, INT_MAX));
    vector<vector<int>> radj(n, vector<int>(n, INT_MAX));
    s--, g1--, g2--;

    for (int i = 0; i < n; ++i) {
        adj[i][i] = 0;
        radj[i][i] = 0;
    }

    for (const auto& edge : edges) {
        int b1 = edge[0] - 1;
        int b2 = edge[1] - 1;
        int c = edge[2];
        adj[b1][b2] = c;
        radj[b2][b1] = c;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adj[i][k] != INT_MAX && adj[k][j] != INT_MAX) {
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
                }
                if (radj[i][k] != INT_MAX && radj[k][j] != INT_MAX) {
                    radj[i][j] = min(radj[i][j], radj[i][k] + radj[k][j]);
                }
            }
        }
    }

    int minc = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (adj[s][i] != INT_MAX && adj[i][g1] != INT_MAX && adj[i][g2] != INT_MAX) {
            minc = min(minc, adj[s][i] + adj[i][g1] + adj[i][g2]);
        }
    }

    return minc;
}

vector<vector<int>> generateInput(int n, int m) {
    vector<vector<int>> edges(m, vector<int>(3));
    for (int i = 0; i < m; ++i) {
        edges[i][0] = rand() % n + 1;
        edges[i][1] = rand() % n + 1;
        edges[i][2] = rand() % 1000 + 1;
    }
    return edges;
}