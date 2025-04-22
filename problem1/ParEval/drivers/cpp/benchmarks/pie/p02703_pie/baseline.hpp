#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef vector<ll> vec;

typedef vector<vec> mat;

typedef pair<ll,ll> pll;

const ll mod=1e9+7;

const ll inf=5e18;

struct E{ll to,co,ti;};

struct P{ll ti,id,re;};

bool operator <(const P &a,const P &b) {return a.ti>b.ti;}

vector<ll> baseline(ll n, ll m, ll s, vector<tuple<ll, ll, ll, ll>>& edges, vector<pll>& costs) {
    vector<vector<E>> edge(n);
    vector<vector<ll>> dp(n, vector<ll>(5001, 0));
    vector<ll> ans(n, 0);
    priority_queue<P> que;

    for(ll i=0;i<m;i++) {
        ll u,v,a,b;
        tie(u, v, a, b) = edges[i];
        u--;v--;
        edge[u].push_back({v,a,b});
        edge[v].push_back({u,a,b});
    }

    vector<ll> c(n), d(n);
    for(ll i=0;i<n;i++) {
        c[i] = costs[i].first;
        d[i] = costs[i].second;
    }

    que.push({1,0,min(5000LL,s)});
    while(que.size()) {
        P p=que.top();
        que.pop();
        if(dp[p.id][p.re])continue;
        dp[p.id][p.re]=p.ti;
        if(!ans[p.id])ans[p.id]=p.ti;
        for(E q:edge[p.id]) {
            if(p.re>=q.co&&!dp[q.to][p.re-q.co]) {
                que.push({p.ti+q.ti,q.to,p.re-q.co});
            }
        }
        if(p.re+c[p.id]<=5000) que.push({p.ti+d[p.id],p.id,p.re+c[p.id]});
    }

    for(ll i=1;i<n;i++) ans[i]--;
    return ans;
}

vector<tuple<ll, ll, ll, ll>> generateInput(ll n, ll m) {
    vector<tuple<ll, ll, ll, ll>> edges;
    for(ll i=0;i<m;i++) {
        ll u = rand() % n + 1;
        ll v = rand() % n + 1;
        ll a = rand() % 1000 + 1;
        ll b = rand() % 1000 + 1;
        edges.push_back(make_tuple(u, v, a, b));
    }
    return edges;
}

vector<pll> generateCosts(ll n) {
    vector<pll> costs;
    for(ll i=0;i<n;i++) {
        ll c = rand() % 1000 + 1;
        ll d = rand() % 1000 + 1;
        costs.push_back({c, d});
    }
    return costs;
}