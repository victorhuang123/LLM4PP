#pragma once

#include<vector>
#include<set>
#include<map>
#include<queue>
using namespace std;

int baseline(int n, vector<pair<int, int>>& edges) {
    int N = n;
    set<int> E[N+1];
    map<int,int> cnt[N+1];
    queue<pair<int,int>> Q;
    int fa[N+1] = {0};

    auto Root = [&](int x) {
        return fa[x]==0?x:(fa[x]=Root(fa[x]));
    };

    auto Link = [&](int u, int v) {
        E[u].insert(v);
        E[v].insert(u);
        if(u>v)
            swap(u,v);
        cnt[u][v]++;
        if(cnt[u][v]>2) {
            return;
        }
        if(cnt[u][v]==2)
            Q.emplace(u,v);
    };

    auto Cut = [&](int u, int v) {
        E[u].erase(v);
        if(u>v)
            swap(u,v);
        cnt[u].erase(v);
    };

    for(int i=1; i<=2*N-2; i++) {
        int u = edges[i-1].first;
        int v = edges[i-1].second;
        Link(u, v);
    }
    for(int i=1; i<N; i++) {
        int u, v;
        do {
            if(Q.empty()) {
                return 0;
            }
            u = Root(Q.front().first);
            v = Root(Q.front().second);
            Q.pop();
        } while(u == v);
        if(E[u].size() < E[v].size())
            swap(u, v);
        fa[v] = u;
        Cut(u, v);
        for(auto e : E[v]) {
            int t = Root(e);
            if(t == u)
                continue;
            Link(t, u);
            Cut(t, v);
        }
    }
    return 1;
}