#pragma once

#include <vector>
#include <utility>

using namespace std;

int baseline(int n, const vector<pair<int, int>>& edges) {
    const int mod = 1e9 + 7;
    const int N = 5000 + 10;

    struct edge { int v, nxt; } e[N << 1];
    int head[N];

    inline void addEdge(int u, int v) {
        static int e_cnt = 0;
        e[++e_cnt] = (edge){v, head[u]}, head[u] = e_cnt;
    }

    int sz[N];
    int f[N][N], g[N], tmp[N];

    inline void dfs(int u, int fa) {
        sz[u] = f[u][1] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v; if (v == fa) continue;
            dfs(v, u);
            for (int j = 1; j <= sz[u] + sz[v]; ++j) tmp[j] = 0;
            for (int j = 1; j <= sz[u]; ++j)
                for (int k = 0; k <= sz[v]; ++k)
                    tmp[j + k] = (tmp[j + k] + 1ll * f[u][j] * f[v][k]) % mod;
            sz[u] += sz[v];
            for (int j = 1; j <= sz[u]; ++j) f[u][j] = tmp[j];
        }
        for (int i = 2; i <= sz[u]; i += 2)
            f[u][0] = (f[u][0] - 1ll * f[u][i] * g[i] % mod + mod) % mod;
    }

    for (int i = 1; i <= n; ++i) head[i] = 0;
    for (const auto& edge : edges) {
        int u = edge.first, v = edge.second;
        addEdge(u, v), addEdge(v, u);
    }

    g[0] = 1;
    for (int i = 2; i <= n; i += 2) g[i] = 1ll * g[i - 2] * (i - 1) % mod;

    dfs(1, 0);
    return f[1][0];
}

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.emplace_back(i - 1, i);
    }
    return edges;
}