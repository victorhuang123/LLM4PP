#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll inf = 1e9;

#define sz              300005

vector<int> baseline(int n, int m, vector<pair<int, int>>& edges) {
    vector<int> par(sz, 0);
    vector<bool> vis(sz, false);
    vector<vector<int>> V(sz);

    for(int i=0; i<m; i++){
        int a = edges[i].first;
        int b = edges[i].second;
        V[a].push_back(b);
        V[b].push_back(a);
    }

    queue<int> q;
    q.push(1);
    vis[1] = true;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int v : V[u]){
            if(!vis[v]){
                par[v] = u;
                vis[v] = true;
                q.push(v);
            }
        }
    }

    vector<int> result;
    for(int i=2; i<=n; i++){
        if(par[i] == 0){
            return {-1};
        }
        result.push_back(par[i]);
    }
    return result;
}

vector<pair<int, int>> generateInput() {
    int n = 300000;
    int m = 300000;
    vector<pair<int, int>> edges;
    for(int i = 1; i <= m; i++) {
        edges.push_back({i, i+1});
    }
    return edges;
}