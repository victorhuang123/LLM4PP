#pragma once

#include<vector>
#include<cstdio>
#include<cstdlib>

#define min(a,b) (a<b?a:b)
const int clz=998244353;
#define mod clz

long long matm(long long val,long long k){
    long long ret=1;
    while(k){
        if(k&1) ret=ret*val%mod;
        k>>=1; val=val*val%mod;
    }
    return ret;
}

inline long long C(int n,int m, const std::vector<long long>& pu, const std::vector<long long>& inv){
    if(m<0||m>n) return 0;
    return (pu[n]*inv[m]%mod)*inv[n-m]%mod;
}

long long getans(int val, int k, int n, const std::vector<long long>& pu, const std::vector<long long>& inv, const std::vector<long long>& pw){
    if(val&1){
        long long ans=0;
        int gro=min(k-val/2,val/2);
        int p=k-gro*2;
        for(int i=(p==0)?1:0;i<=gro;i++) {
            ans+=(C(n+p-1,i+p-1,pu,inv)*pw[i]%mod)*C(gro,i,pu,inv)%mod; 
            ans%=mod;
        }
        return ans;
    }
    else{
        long long ans=0;
        int gro=min(k-val/2+1,val/2);
        int p=k-gro*2+1;
        for(int i=(p==0)?1:0;i<gro;i++) {
            ans+=(C(n+p-1,i+p-1,pu,inv)*pw[i]%mod)*C(gro-1,i,pu,inv)%mod; 
            ans%=mod;
        }
        for(int i=(p==0)?1:0;i<gro;i++) {
            ans+=(C(n+p-2,i+p-1,pu,inv)*pw[i]%mod)*C(gro-1,i,pu,inv)%mod; 
            ans%=mod;
        }
        return ans;
    }
}

std::vector<long long> baseline(int k, int n){
    std::vector<long long> pu(100005), pw(100005), inv(100005);
    pu[0]=pw[0]=1;
    for(int i=1;i<=100000;i++) pu[i]=pu[i-1]*i%mod;
    for(int i=1;i<=100000;i++) pw[i]=pw[i-1]*2%mod;
    inv[100000]=matm(pu[100000],mod-2);
    for(int i=99999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;

    std::vector<long long> result;
    for(int i=2;i<=2*k;i++) result.push_back(getans(i,k,n,pu,inv,pw));
    return result;
}

std::pair<int, int> generate_input() {
    return {100000, 100000};
}