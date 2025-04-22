#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll baseline(int n, int m, vector<int>& A, vector<int>& B, vector<vector<int>>& E) {
    vector<int> C(n + 1), Fa(n + 1), P(n + 1), Vis(n + 1);
    vector<ll> F(n + 1), Sum(n + 1);
    vector<vector<int>> T(n + 1);

    auto cmp = [&](const int a, const int b) { return C[a] < C[b]; };
    auto find = [&](const int a) { return a == Fa[a] ? a : Fa[a] = find(Fa[a]); };

    for (int i = 1; i <= n; i++) {
        C[i] = max(A[i] - B[i], 0);
        P[i] = Fa[i] = i;
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u = E[i][0], v = E[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    sort(P.begin() + 1, P.end(), cmp);

    for (int i = 1; i <= n; i++) {
        int u = P[i], f;
        Vis[u] = 1;
        for (int v : adj[u])
            if (Vis[v] && (f = find(v)) != u) {
                Fa[f] = u;
                T[u].push_back(f);
            }
    }

    function<void(int)> dfs = [&](int u) {
        Sum[u] = B[u];
        for (int v : T[u]) {
            dfs(v);
            Sum[u] += Sum[v];
        }
        if (T[u].empty())
            F[u] = C[u] + B[u];
        else {
            F[u] = LLONG_MAX;
            for (int v : T[u])
                F[u] = min(F[u], max(F[v], (ll)C[u]) + Sum[u] - Sum[v]);
        }
    };

    dfs(P[n]);
    return F[P[n]];
}

vector<vector<int>> generateInput(int n, int m) {
    vector<vector<int>> E(m, vector<int>(2));
    for (int i = 0; i < m; i++) {
        E[i][0] = rand() % n + 1;
        E[i][1] = rand() % n + 1;
    }
    return E;
}