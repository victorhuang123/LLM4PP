#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> baseline(int N, vector<int>& colors, vector<pair<int, int>>& edges) {
    vector<int> C(N + 1);
    vector<ll> kotae(N + 1, 0);
    vector<int> K(N + 1, 0);
    vector<vector<int>> E(N + 1);
    int zentai = 0;

    rep1(i, N) C[i] = colors[i-1];
    rep(i, N-1) {
        int a = edges[i].first;
        int b = edges[i].second;
        E[a].pb(b);
        E[b].pb(a);
    }

    function<void(int, int)> dfs = [&](int p, int mae) {
        int k = K[C[p]] + zentai;
        int k0 = k;

        for (int to : E[p]) {
            if (mae != to) {
                dfs(to, p);
                int sa = K[C[p]] + zentai - k;
                kotae[C[p]] -= ll(sa) * (sa + 1) / 2;
                k += sa;
            }
        }

        zentai++;
        K[C[p]] = k0 - zentai;
    };

    dfs(1, -1);
    ll n = ll(N) * (N + 1) / 2;
    vector<ll> result(N);
    rep1(i, N) {
        int sa = K[i] + zentai;
        result[i-1] = n + kotae[i] - ll(sa) * (sa + 1) / 2;
    }
    return result;
}

vector<int> generateInput(int N) {
    vector<int> colors(N);
    vector<pair<int, int>> edges(N - 1);
    for (int i = 0; i < N; i++) {
        colors[i] = i + 1;
    }
    for (int i = 0; i < N - 1; i++) {
        edges[i] = {i + 1, i + 2};
    }
    return {N, colors, edges};
}