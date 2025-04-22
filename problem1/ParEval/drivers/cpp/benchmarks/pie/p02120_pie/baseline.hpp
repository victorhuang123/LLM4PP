#pragma once

#include<bits/stdc++.h>
using namespace std;

typedef long long int64;

vector<int64> baseline(int N, int M, vector<int>& W, vector<pair<int, int>>& edges) {
    vector< int > g[N];
    bool v[N];
    int order[N], low[N], ptr = 0;
    int64 sum[N], ans[N];
    vector< int > tree[N];

    for(auto &edge : edges) {
        int a = edge.first, b = edge.second;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    function<void(int, int)> dfs = [&](int idx, int par) {
        v[idx] = true;
        order[idx] = ptr++;
        low[idx] = order[idx];
        sum[idx] = W[idx];
        for(auto &to : g[idx]) {
            if(!v[to]) {
                dfs(to, idx);
                low[idx] = min(low[idx], low[to]);
                sum[idx] += sum[to];
                tree[idx].emplace_back(to);
            } else if(to != par) {
                low[idx] = min(low[idx], order[to]);
            }
        }
    };

    function<void(int, int64)> dfs2 = [&](int idx, int64 parcost) {
        bool art = false;
        int64 all = parcost;
        if(idx == 0) {
            if(tree[idx].size() > 1) art = true;
            else art = false;
        } else {
            for(auto &to : tree[idx]) art |= order[idx] <= low[to];
        }
        for(auto &to : tree[idx]) all += sum[to];
        if(art) {
            int64 latte = parcost, malta = 0;
            for(auto &to : tree[idx]) {
                if(order[idx] <= low[to]) malta = max(malta, sum[to]);
                else latte += sum[to];
            }
            ans[idx] = max(latte, malta);
        } else {
            ans[idx] = sum[0] - W[idx];
        }
        for(auto &to : tree[idx]) dfs2(to, all + W[idx] - sum[to]);
    };

    dfs(0, -1);
    dfs2(0, 0);

    return vector<int64>(ans, ans + N);
}

vector<pair<int, int>> generateInput(int N, int M) {
    vector<pair<int, int>> edges;
    for(int i = 1; i < N; ++i) {
        edges.emplace_back(0, i);
    }
    for(int i = N; i <= M; ++i) {
        int a = rand() % N;
        int b = rand() % N;
        edges.emplace_back(a, b);
    }
    return edges;
}