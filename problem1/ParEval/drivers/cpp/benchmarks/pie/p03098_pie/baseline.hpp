#pragma once

#include<bits/stdc++.h>

#define rep(i,a,b) for(int i=(a);i<=(b);i++)

#define per(i,a,b) for(int i=(a);i>=(b);i--)

#define REP(i,n) for(int i=(0);i<(n);i++)

#define fi first

#define se second

#define pb push_back

#define mp make_pair

using namespace std;

typedef pair<int,int> pii;

typedef vector<int> vi;

typedef long long ll;

vi rev(vi a){
    int n = a.size() - 1;
    vi b(n+1,0);
    rep(i,1,n)b[a[i]]=i;
    return b;
}

vi mul(vi a,vi b){
    int n = a.size() - 1;
    vi c(n+1,0);
    rep(i,1,n)c[i]=a[b[i]];
    return c;
}

vi power(vi a,int p){
    int n = a.size() - 1;
    vi res(n+1,0);
    rep(i,1,n)res[i]=i;
    for(;p;p>>=1,a=mul(a,a))
        if(p&1)res=mul(res,a);
    return res;
}

vi baseline(int n, int K, vi p, vi q){
    vi A, B[10], res;
    A=power(mul(q,mul(rev(p),mul(rev(q),p))),(K-1)/6);
    if(K%6==4)A=mul(A,q);
    if(K%6==5||K%6==0)A=mul(A,mul(q,rev(p)));
    B[1]=p;
    B[2]=q;
    B[3]=mul(q,rev(p));
    B[4]=rev(p);
    B[5]=rev(q);
    B[6]=mul(rev(q),p);
    res=mul(A,mul(B[(K-1)%6+1],rev(A)));
    return res;
}

vi generateInput(int n){
    vi p(n+1), q(n+1);
    rep(i,1,n)p[i]=i;
    rep(i,1,n)q[i]=n-i+1;
    return p, q;
}