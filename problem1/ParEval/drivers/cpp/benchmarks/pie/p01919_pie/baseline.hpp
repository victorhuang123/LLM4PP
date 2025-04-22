#pragma once

#include <bits/stdc++.h>

using namespace std;

#define rep(i,n) for(int i=0;i<n;++i)

typedef long long ll;

struct edge{int to;ll cost;};

ll baseline(int n, int m, vector<int>& x, vector<int>& y, vector<ll>& t, int v0, int a, int b, int c) {
    vector<vector<edge>> G(60000);
    vector<ll> dp(60000, LLONG_MAX);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> qu;

    auto nextv = [&](int v, int a, int b, int c) { return (a*v+b)%c; };

    rep(i,m)rep(v,c){
        G[x[i]*c+v].push_back({y[i]*c+nextv(v,a,b,c),t[i]*v});
        G[y[i]*c+v].push_back({x[i]*c+nextv(v,a,b,c),t[i]*v});	
        G[((n-1)*2-x[i])*c+v].push_back({((n-1)*2-y[i])*c+nextv(v,a,b,c),t[i]*v});
        G[((n-1)*2-y[i])*c+v].push_back({((n-1)*2-x[i])*c+nextv(v,a,b,c),t[i]*v});
    }

    dp[v0]=0;
    qu.push({0,v0});

    while(qu.size()){
        pair<ll,int> u = qu.top();
        qu.pop();

        if(u.second/c==2*(n-1)){
            return dp[u.second];			
        }

        if(dp[u.second] < u.first)continue;

        for(auto e:G[u.second]){
            if(dp[e.to] > dp[u.second] + e.cost){
                dp[e.to] = dp[u.second] + e.cost;
                qu.push({dp[e.to],e.to});
            }
        }
    }
    return -1;
}

vector<int> generateInput(int n, int m, int c) {
    vector<int> x(m), y(m);
    vector<ll> t(m);
    rep(i, m) {
        x[i] = rand() % n;
        y[i] = rand() % n;
        t[i] = rand() % 1000000 + 1;
    }
    return {n, m, c, x, y, t};
}