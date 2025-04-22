#pragma once

#include<iostream>
#include<map>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

typedef pair<int,int> P;
typedef pair<int,P> P2;

const int INF = 100000000;

int baseline(int n, int m, int l, int k, vector<vector<P>>& G, int s, int g, vector<int>& b) {
    int dis[51][1<<7][10], vis[51][1<<7];

    for(int i=1;i<=n;i++)
        for(int j=0;j<(1<<l);j++){
            for(int x=0;x<k;x++) dis[i][j][x] = INF;
            vis[i][j] = 0;
        }

    int st = 0;
    for(int i=0;i<l;i++) if(s==b[i]) st |= 1<<i;

    priority_queue< P2,vector<P2>,greater<P2> > q;
    q.push(P2(0,P(s,st)));

    while(q.size()){
        P2 p = q.top(); q.pop();
        int dist = p.first, pos = p.second.first, state = p.second.second;

        if(vis[pos][state] < k){
            dis[pos][state][vis[pos][state]] = dist;
            vis[pos][state]++;
        } else continue;

        for(int i=0;i<G[pos].size();i++){
            int cost = G[pos][i].first, nxt = G[pos][i].second;
            int nstate = state;
            for(int j=0;j<l;j++) if(nxt==b[j]) nstate |= 1<<j;

            if(vis[nxt][nstate] < k) q.push(P2(dist+cost,P(nxt,nstate)));
        }
    }

    int res = dis[g][(1<<l)-1][k-1];
    return res == INF ? -1 : res;
}

vector<vector<P>> generateInput(int n, int m, int l, int k, int s, int g, vector<int>& b) {
    vector<vector<P>> G(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        u = rand() % n + 1;
        v = rand() % n + 1;
        w = rand() % 100 + 1;
        G[u].push_back({w, v});
    }
    for (int i = 0; i < l; i++) {
        b[i] = rand() % n + 1;
    }
    return G;
}