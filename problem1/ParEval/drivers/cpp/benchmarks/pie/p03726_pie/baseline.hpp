#pragma once

#include<bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 15;

string baseline(int n, vector<pair<int, int>>& edges) {
    int cnt[maxn] = {0};
    bool is[maxn] = {false};
    set<int> st[maxn];
    vector<int> g[maxn];

    for(int i = 0; i < n - 1; i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        u--, v--;
        cnt[u]++;
        cnt[v]++;
        st[u].insert(v);
        st[v].insert(u);        
        g[u].push_back(v);
        g[v].push_back(u);
    }

    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(cnt[i] == 1) {
            q.push(i);
        }
    }

    while(q.size()) {
        int u = q.front();
        if(!cnt[u]) {
            return "First";
        }
        int v = *st[u].begin();
        is[u] = true;
        is[v] = true;
        for(auto it = st[v].begin(); it != st[v].end(); it++) {
            cnt[*it]--;
            st[*it].erase(v);
            if(cnt[*it] == 1)
                q.push(*it);
        }
        q.pop();
    }

    string a = "Second";
    for(int i = 0; i < n; i++) {
        if(!is[i])
            a = "First";
    }
    return a;
}