#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ull unsigned long long
#define ll long long

const int maxn=200005;
const ull b=1000000007;

ll baseline(int n, vector<pair<int, int>>& edges) {
    ll ans = 0;
    map<ull, ll> m;
    vector<vector<int>> g(n + 1);
    vector<ull> dp(n + 1);

    for (auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    function<void(int, int)> dfs = [&](int u, int p) {
        dp[u] = 1;
        for (int v : g[u]) {
            if (v == p) continue;
            dfs(v, u);
            dp[u] += dp[v] * b;
        }
        ans += m[dp[u]];
        m[dp[u]]++;
    };

    dfs(1, -1);
    return ans;
}

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.emplace_back(i, i / 2);
    }
    return edges;
}