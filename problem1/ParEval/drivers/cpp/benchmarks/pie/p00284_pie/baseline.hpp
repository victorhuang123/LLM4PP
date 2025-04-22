#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i,b) for(ll i=0; i<ll(b); i++)

int popcount(unsigned long long x){
    static int dp[66000];
    if(dp[65536] != 16) for(int i = 0; i < 65536; i++) dp[i] = (i&1) + dp[i>>1];
    int res = 0;
    while(x) res += dp[x&65535], x >>= 16;
    return res;
}

int solve(ll s, ll d){
    if(s <= 0 && d >= 0) return popcount(-s) + popcount(d);
    else if(s >= 0 && d >= 0){
        int j = 0;
        int ans = 0;
        while(s < d){
            if((s>>j&1) && (d>>j&1)){
                s += 1LL<<j;
                d -= 1LL<<j;
                ans += 2;
            } else if((s>>j&1) ^ (d>>j&1)){
                s += 1LL<<j;
                ans ++;
            }
            j++;
        }
        return ans;
    } else return solve(-d,-s);
}

vector<int> baseline(int N, vector<pair<ll, ll>>& queries){
    vector<int> results(N);
    rep(i,N){
        ll s = queries[i].first;
        ll d = queries[i].second;
        results[i] = solve(s,d);
    }
    return results;
}

vector<pair<ll, ll>> generate_input(int N){
    vector<pair<ll, ll>> queries(N);
    rep(i,N){
        queries[i].first = rand() % 1000000000;
        queries[i].second = rand() % 1000000000;
    }
    return queries;
}