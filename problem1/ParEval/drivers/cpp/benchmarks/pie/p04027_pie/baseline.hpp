#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int O=510;
const ll mod=1e9+7;

ll baseline(int n, int c, vector<int>& a, vector<int>& b) {
    vector<vector<ll>> f(O, vector<ll>(O, 0));
    vector<vector<ll>> bin(O, vector<ll>(O, 0));

    for(int i=1;i<O;++i) bin[i][0]=1;
    for(int i=1;i<O;++i)
        for(int j=1;j<O;++j)
            bin[i][j]=bin[i][j-1]*i%mod;

    for(int i=1;i<O;++i)
        for(int j=0;j<O;++j)
            bin[i][j]=(bin[i-1][j]+bin[i][j])%mod;

    f[0][0]=1;
    for(int i=1;i<=n;++i)
        for(int j=0;j<=c;++j)
            for(int k=0;k<=j;++k)
                (f[i][j]+=f[i-1][j-k]*((bin[b[i]][k]-bin[a[i]-1][k])%mod+mod)%mod)%=mod;

    return f[n][c];
}

vector<int> generateInput(int n) {
    vector<int> a(n+1), b(n+1);
    for(int i=1;i<=n;++i) {
        a[i] = rand() % O + 1;
        b[i] = rand() % O + 1;
        if(a[i] > b[i]) swap(a[i], b[i]);
    }
    return a, b;
}