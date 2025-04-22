#pragma once

#include<bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=(a); i<(b); i++)

vector<vector<int>> baseline(int n, int l, int r, int t) {
    vector<vector<int>> G(n, vector<int>(n, 0));

    if(l+1 == r) return G;

    int m = (l+r) / 2;

    rep(i,l,m) rep(j,m,r) G[i][j] = t;

    auto left = baseline(n, l, m, t+1);
    auto right = baseline(n, m, r, t+1);

    rep(i,0,n) rep(j,0,n) {
        if(i >= l && i < m && j >= m && j < r) continue;
        G[i][j] = max(left[i][j], right[i][j]);
    }

    return G;
}

vector<vector<int>> generateInput(int n) {
    return vector<vector<int>>(n, vector<int>(n, 0));
}