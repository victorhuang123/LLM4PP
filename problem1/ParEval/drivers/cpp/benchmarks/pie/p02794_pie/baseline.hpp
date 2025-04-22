#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll baseline(int N, int M, vector<pair<int, int>> edges, vector<pair<int, int>> queries) {
    vector<vector<int>> V(N + 1);
    vector<vector<pair<int, int>>> E(N + 1);
    ll dp[1 << 20] = {0};

    for (int i = 0; i < N - 1; i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        E[a].push_back({b, i});
        E[b].push_back({a, i});
    }

    function<void(int, vector<int>, int)> dfs = [&](int p, vector<int> v, int mae) {
        V[p] = v;
        for (auto pr : E[p]) {
            int to = pr.first;
            if (mae != to) {
                v.push_back(pr.second);
                dfs(to, v, p);
                v.pop_back();
            }
        }
    };

    vector<int> kari;
    dfs(1, kari, 0);

    int list[51] = {0};
    for (int i = 0; i < M; i++) {
        int u = queries[i].first;
        int v = queries[i].second;
        for (int j : V[u]) list[j] ^= 1 << i;
        for (int j : V[v]) list[j] ^= 1 << i;
    }

    dp[0] = 1;
    for (int i = 0; i < N - 1; i++) {
        for (int j = (1 << M) - 1; j >= 0; j--) {
            dp[j | list[i]] += dp[j];
        }
    }

    return dp[(1 << M) - 1];
}

vector<pair<int, int>> generate_input_edges(int N) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < N; i++) {
        edges.push_back({i, i + 1});
    }
    return edges;
}

vector<pair<int, int>> generate_input_queries(int M) {
    vector<pair<int, int>> queries;
    for (int i = 0; i < M; i++) {
        queries.push_back({1, 2});
    }
    return queries;
}