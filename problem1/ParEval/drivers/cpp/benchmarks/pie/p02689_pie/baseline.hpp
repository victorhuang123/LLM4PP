#pragma once

#include<bits/stdc++.h>

#define p_ pair<int,int>

#define mp_ make_pair

#define ll long long

#define pb push_back

#define fi first

#define se second

#define rep(i,a,b) for(int i=a;i<=b;i++)

using namespace std;

const int maxn = 2e5+5;

int baseline(int n, int m, vector<int>& a, vector<vector<int>>& g) {
    int ans = 0;
    rep(i,1,n){
        int sz = g[i].size();
        int flag = 1;
        for(int v:g[i]) if(a[v]>=a[i]) {flag=0;break;}
        if(flag) ans++;
    }
    return ans;
}

vector<int> generateInputA(int n) {
    vector<int> a(n + 1);
    rep(i,1,n) a[i] = rand() % 1000000 + 1;
    return a;
}

vector<vector<int>> generateInputG(int n, int m) {
    vector<vector<int>> g(n + 1);
    rep(i,1,m) {
        int u = rand() % n + 1;
        int v = rand() % n + 1;
        if(u != v) g[u].pb(v);
    }
    return g;
}