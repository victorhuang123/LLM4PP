#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define P pair<ll,ll>

#define FOR(I,A,B) for(ll I = (A); I < (B); ++I)

#define FORR(I,A,B) for(ll I = ((B)-1); I >= (A); --I)

#define TO(x,t,f) ((x)?(t):(f))

#define SORT(x) (sort(x.begin(),x.end())) // 0 2 2 3 4 5 8 9

#define REV(x) (reverse(x.begin(),x.end())) //reverse

ll gcd(ll a,ll b){if(a<b)swap(a,b);if(a%b==0)return b;return gcd(b,a%b);}

ll lcm(ll a,ll b){ll c=gcd(a,b);return ((a/c)*(b/c)*c);}//saisyo kobaisu

#define NEXTP(x) next_permutation(x.begin(),x.end())

const ll INF=1e18+7;

const ll MOD=1e9+7;

vector<ll> generateInput() {
    return {100000};
}

vector<vector<ll>> baseline(ll N) {
    vector<ll> Yes(100001,0);
    FOR(i,0,100001){
        ll x = i*8 + 1;
        ll p = sqrt(x);
        if(p*p==x){
            Yes[i]=(1+p)/2;
        }
    }
    if(Yes[N]==0){
        return {};
    }
    ll K = Yes[N];
    bool same[K+1][K+1]={false};
    vector< vector<ll> > Si;
    Si.resize(K+1);
    ll num=1;
    FOR(i,1,K+1){
        FOR(j,1,K+1){
            if(j==i)continue;
            if(not same[i][j]){
                same[i][j] = same[j][i] = true;
                Si[i].push_back(num);
                Si[j].push_back(num);
                num++;
            }
        }
    }
    vector<vector<ll>> result;
    result.push_back({K});
    FOR(i,1,K+1){
        vector<ll> row;
        row.push_back(Si[i].size());
        FOR(j,0,Si[i].size()){
            row.push_back(Si[i][j]);
        }
        result.push_back(row);
    }
    return result;
}