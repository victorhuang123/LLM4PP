#pragma once

#include<bits/stdc++.h>

#define INF 1e9
#define llINF 1e18
#define MOD 1000000007
#define pb push_back
#define mp make_pair 
#define F first
#define S second
#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define BITLE(n) (1LL<<(n))
#define BITCNT(n) (__builtin_popcountll(n))
#define SUBS(s,f,t) (s.substr(f-1,t-f+1))
#define ALL(a) (a).begin(),(a).end()

using namespace std;

struct Grid{ll x,y,t;};
struct Edge{ll to,cost;};
struct Graph{vector<vector<Edge>>E;int V;
  const ll Inf = llINF;const int MAX_V=201010;vector<ll>d;
  Graph(int n):E(n){d.resize(MAX_V);E.resize(n);V=n;}
  void init(){for(int i=0;i<MAX_V;i++)d[i]=Inf;}
  void add_edge(ll from,ll to,ll cost){E[from].pb({to,cost});}
};

vi hog(100010);

bool baseline(ll a, ll b) {
    return (a + 1) / 2 >= b;
}

vi generateInput() {
    vi input = {1000000000, 500000000};
    return input;
}