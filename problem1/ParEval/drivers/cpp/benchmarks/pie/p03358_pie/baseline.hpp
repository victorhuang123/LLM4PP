#pragma once

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

#define rint register int

inline int read(){int r;int s=0,c;for(;!isdigit(c=getchar());s=c);for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);return s^45?r:-r;}

int baseline(int n, const string& input) {
    vector<int> e[MAXN+5]; int s[MAXN+5], c[MAXN+5], r, f, m, Ans = 0; string S = "B" + input;

    for(rint i = 2, a, b; i <= n; a = read(), b = read(), e[a].push_back(b), e[b].push_back(a), i++);

    if((r=S.find('W'))==-1) return 0;
    
    auto DFS = [&](int p, int fa) {
        s[p] = S[p]=='W', c[p] = (S[p]!='B')^!!fa; 
        for(auto v:e[p]) if(v^fa) DFS(v,p), s[p] += s[v], c[p] ^= !!s[v];
    };

    auto Dia = [&](int p, int fa, int d) {
        d>m||(d==m&&!c[p])?m=d,f=p:0; 
        for(auto v:e[p]) if(s[v]&&v^fa) Dia(v,p,d+(c[v]<<1));
    };

    auto Cal = [&](int p, int fa) {
        Ans += c[p]; 
        for(auto v:e[p]) if(s[v]&&v^fa) Cal(v,p), Ans += 2;
    };

    DFS(r,0), Cal(r,0), Dia(f=r,0,m=c[r]<<1), Dia(r=f,0,m=c[f]<<1);
    return Ans-m+((c[r]&&c[f])<<1);
}

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({1, i});
    }
    return edges;
}