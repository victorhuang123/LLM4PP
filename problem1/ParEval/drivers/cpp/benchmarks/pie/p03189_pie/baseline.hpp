#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N=3e3+100,mod=1e9+7,inv2=(mod+1)>>1;

void Inc(int &x,int y) {x+=y, x=x>=mod?x-mod:x;}

int qpow(LL x,int y) {
    LL ret=1;
    while(y) {
        if(y&1) ret=ret*x%mod;
        x=x*x%mod, y>>=1;
    }
    return ret;
}

int baseline(int n, int Q, vector<int>& a, vector<pair<int, int>>& queries) {
    vector<vector<int>> f(n+1, vector<int>(n+1));
    vector<int> fx(n+1), gx(n+1);
    int Ans = 0;

    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            f[i][j]=(a[i]>a[j])?1:0;

    for(int q=0;q<Q;++q) {
        int x = queries[q].first, y = queries[q].second;
        if(x == y) continue;
        for(int i=1;i<=n;++i)
            fx[i]=1ll*inv2*(f[x][i]+f[y][i])%mod,
            gx[i]=1ll*inv2*(f[i][x]+f[i][y])%mod;
        fx[y]=1ll*inv2*(f[x][y]+f[y][x])%mod;
        for(int i=1;i<=n;++i)
            f[x][i]=fx[i], f[i][x]=gx[i],
            f[y][i]=fx[i], f[i][y]=gx[i];
        f[x][y]=f[y][x]=fx[y], f[x][x]=f[y][y]=0;
    }

    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j) Inc(Ans,f[i][j]);

    Ans=1ll*Ans*qpow(2,Q)%mod;
    return Ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n+1);
    for(int i=1;i<=n;++i) a[i] = rand() % mod;
    return a;
}

vector<pair<int, int>> generateQueries(int Q, int n) {
    vector<pair<int, int>> queries(Q);
    for(int i=0;i<Q;++i) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        queries[i] = {x, y};
    }
    return queries;
}