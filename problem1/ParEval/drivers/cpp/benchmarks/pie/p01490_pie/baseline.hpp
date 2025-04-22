#pragma once

#include<bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i,n) for(int i=0;i<(n);i++)
#define pb push_back
#define all(v) (v).begin(),(v).end()
#define fi first
#define se second
typedef vector<int>vint;
typedef pair<int,int>pint;
typedef vector<pint>vpint;

template<typename A,typename B>inline void chmin(A &a,B b){if(a>b)a=b;}
template<typename A,typename B>inline void chmax(A &a,B b){if(a<b)a=b;}

#define double long double

const int INF=1001001001;
const int INFLL=1001001001001001001ll;
const int mod=1000000007;
inline void add(int &a,int b){
    a+=b;
    if(a>=mod)a-=mod;
}
const double PI=acos(-1);
const double EPS=1e-7;

double baseline(int N, vint R) {
    sort(all(R));
    reverse(all(R));
    double ans=0;

    for(int k=3;k<=N;k++){
        vint r(R.begin(),R.begin()+k);
        sort(all(r));
        do{
            vector<double>L(k);
            rep(i,k)L[i]=r[i]*r[(i+1)%k]/2.0;
            double mi=*min_element(all(L));
            double lb=-mi;
            double ub=mi;
            rep(i,100){
                double mid=(ub+lb)/2;
                double sum=0;
                rep(j,k)sum+=acos(mid/L[j]);
                if(sum>=2*PI)lb=mid;
                else ub=mid;
            }

            double sum=0;
            rep(j,k)sum+=acos(lb/L[j]);
            if(abs(sum-2*PI)>EPS)continue;
            double val=0;
            rep(j,k)val+=sin(acos(lb/L[j]))*L[j];
            chmax(ans,val);
        }while(next_permutation(all(r)));
    }
    return ans;
}

vint generateInput(int N) {
    vint R(N);
    rep(i, N) R[i] = i + 1;
    return R;
}