#pragma once

#include<bits/stdc++.h>

#define rep(i,l,r) for (int i=l;i<=r;i++)

using namespace std;

typedef long long ll;

ll baseline(int n, int k, ll mm) {
    vector<vector<ll>> c(n+1, vector<ll>(n+1, 0));
    c[0][0] = 1;

    rep(i,1,n) {
        c[i][0] = 1; c[i][i] = 1;
        rep(j,1,i-1) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mm;
    }

    vector<vector<ll>> f(n+2, vector<ll>(k+1, -1));
    vector<vector<ll>> g(n+1, vector<ll>(k+1, -1));

    function<ll(int,int)> dfs = [&](int i, int j) {
        if (f[i][j] != -1) return f[i][j];
        if (i == 1) return f[i][j] = 1;
        f[i][j] = 0;
        rep(len,1,i-1) {
            (f[i][j] += g[len][j+1] * dfs(i-len, j) % mm * c[i-2][len-1] % mm) %= mm;
        }
        return f[i][j];
    };

    function<ll(int,int)> getsum = [&](int i, int j) {
        if (g[i][j] != -1) return g[i][j];
        g[i][j] = 0;
        rep(p,j,k) (g[i][j] += dfs(i,p)) %= mm;
        return g[i][j];
    };

    dfs(n+1, 0);
    return f[n+1][0];
}

vector<int> generateInput() {
    int n = 300, k = 300;
    ll mm = 1e9 + 7;
    return {n, k, mm};
}