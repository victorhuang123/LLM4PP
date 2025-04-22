#pragma once

#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=1e5+5;

vector<int> baseline(int n, vector<pair<int, pair<int,int>>>& edge) {
    int pset[N], lazy[N], ans[N];
    vector<int> child[N];

    for(int i=1;i<=n; ++i) pset[i] = i, child[i].push_back(i);

    auto joinset = [&](int u, int v, int w) {
        if(child[ pset[u] ].size() > child[ pset[v] ].size()) swap(u, v);
        int pau = pset[u];
        lazy[ pset[v] ] += w * (child[ pset[u] ].size());
        for(int cu : child[ pset[u] ]) {
            ans[cu] += lazy[ pset[u] ] + w * child[ pset[v] ].size() - lazy[ pset[v] ];
        }
        for(int cu : child[ pset[u] ]) child[ pset[v] ].push_back(cu), pset[cu] = pset[v];
        child[ pau ].clear();
    };

    sort(edge.begin(), edge.end());
    for(int i = edge.size()-1; i >= 0; --i) {
        joinset(edge[i].second.first, edge[i].second.second, edge[i].first);
    }

    vector<int> result(n);
    for(int i = 1; i <= n; ++i) {
        result[i-1] = ans[i] + lazy[ pset[i] ];
    }
    return result;
}

vector<pair<int, pair<int,int>>> generateInput(int n) {
    vector<pair<int, pair<int,int>>> edge;
    for(int i = 1; i <= n; ++i) {
        edge.push_back({i, {i, i+1}});
    }
    return edge;
}