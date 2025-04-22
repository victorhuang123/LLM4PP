#pragma once

#include<bits/stdc++.h>

#define p 998244353

#define int long long 

using namespace std;

inline int POW(int a,int b=p-2,int ans=1){
    for(;b;b>>=1,a=a*a%p)
        if(b&1) ans=ans*a%p;
    return ans;
}

int baseline(int n, int m){
    if(n<m) swap(n,m);
    vector<int> f(n+m+1), inv(n+m+1);
    int ans = 0;
    for(int i=f[0]=inv[0]=1;i<=n+m;i++)
        f[i]=f[i-1]*i%p,inv[i]=POW(f[i]);
    for(int i=1;i<=m;i++)
        ans=(ans+f[i<<1]*inv[i]%p*inv[i]%p*f[n-i+m-i]%p*inv[n-i]%p*inv[m-i]%p)%p;
    ans=ans*inv[2]%p*POW(f[n+m]*inv[n]%p*inv[m]%p)%p;
    return (ans+n)%p;
}

vector<int> generateInput(){
    return {1000000, 1000000};
}