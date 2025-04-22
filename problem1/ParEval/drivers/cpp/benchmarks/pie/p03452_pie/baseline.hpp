#pragma once

#include <bits/stdc++.h>

#define LL long long
#define mp make_pair
#define pb push_back
#define INF (1<<29)

using namespace std;

typedef pair<int,int>pii;

bool baseline(int n, int m, vector<pii> G[]) {
    int vis[n+1], col[n+1];
    memset(vis, -1, sizeof(vis));
    if(m == 0) return true;
    for(int i = 1; i <= n; i++) {
        if(vis[i] != -1) continue;
        memset(col, 0, sizeof(col));
        if(dfs(i, 0, G, col, vis) == 0) return false;
    }
    return true;
}

bool dfs(int x, int co, vector<pii> G[], int col[], int vis[]) {
    if(vis[x] != -1) return col[x] == co;
    vis[x] = 1;
    col[x] = co;
    for(pii i : G[x]) {
        if(dfs(i.first, co + i.second, G, col, vis) == 0) return false;
    }
    return true;
}

vector<pii>* generateInput(int n, int m) {
    vector<pii>* G = new vector<pii>[n+1];
    for(int i = 0; i < m; i++) {
        int u = rand() % n + 1;
        int v = rand() % n + 1;
        int w = rand() % 2;
        G[u].pb(mp(v, w));
        G[v].pb(mp(u, -w));
    }
    return G;
}