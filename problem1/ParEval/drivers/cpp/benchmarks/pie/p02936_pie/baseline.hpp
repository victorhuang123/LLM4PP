#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

vector<int> baseline(int N, int Q, vector<pair<int, int>>& edges, vector<pair<int, int>>& queries) {
    int C[200001];
    int X[200001] = {0};
    vector<int> E[200001];

    rep(i, N - 1) {
        int a = edges[i].first;
        int b = edges[i].second;
        E[a].pb(b);
        E[b].pb(a);
    }

    rep(i, Q) {
        int p = queries[i].first;
        int x = queries[i].second;
        X[p] += x;
    }

    function<void(int, int, int)> dfs = [&](int p, int prev, int c) {
        int k = c + X[p];
        C[p] = k;
        for (int to : E[p]) {
            if (to != prev) dfs(to, p, k);
        }
    };

    dfs(1, 0, 0);

    vector<int> result(N + 1);
    rep1(i, N) result[i] = C[i];
    return result;
}

vector<pair<int, int>> generateInput(int N, int Q) {
    vector<pair<int, int>> edges(N - 1);
    vector<pair<int, int>> queries(Q);

    for (int i = 0; i < N - 1; i++) {
        edges[i] = mp(i + 1, i + 2);
    }

    for (int i = 0; i < Q; i++) {
        queries[i] = mp(1 + (i % N), 1);
    }

    return edges, queries;
}