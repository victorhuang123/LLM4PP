#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long

const int N=2005;

ll baseline(int n, const vector<char>& s, const vector<vector<int>>& G) {
    ll ans = 1e18;
    vector<int> sz(N);
    vector<ll> f(N), g(N);

    function<void(int, int)> dfs = [&](int x, int p) {
        sz[x] = s[x] == '1';
        g[x] = 0;
        ll mx = 0, sum = 0;

        for (int i = 0; i < G[x].size(); i++) {
            if (G[x][i] != p) {
                int y = G[x][i];
                dfs(y, x);
                sz[x] += sz[y];
                g[y] += sz[y];
                g[x] += g[y];
                f[y] += sz[y];

                if (f[y] >= f[mx]) {
                    sum += g[mx];
                    mx = y;
                } else {
                    sum += g[y];
                }
            }
        }

        if (sum >= f[mx]) {
            f[x] = (sum - f[mx]) & 1;
        } else {
            f[x] = f[mx] - sum;
        }
    };

    for (int i = 1; i <= n; i++) {
        dfs(i, 0);
        if (!f[i]) {
            ans = min(ans, g[i]);
        }
    }

    return ans == 1e18 ? -1 : ans / 2;
}

vector<char> generateInput(int n) {
    vector<char> s(n + 1);
    for (int i = 1; i <= n; i++) {
        s[i] = (rand() % 2) ? '1' : '0';
    }
    return s;
}

vector<vector<int>> generateGraph(int n) {
    vector<vector<int>> G(n + 1);
    for (int i = 2; i <= n; i++) {
        int p = rand() % (i - 1) + 1;
        G[p].push_back(i);
        G[i].push_back(p);
    }
    return G;
}