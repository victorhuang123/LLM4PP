#pragma once

#include <bits/stdc++.h>

#define LL long long
#define ll long long
#define LF double

#define ON(n,i) (n|(1LL<<i))
#define OFF(n,i) (n&(~(1LL<<i)))
#define CHK(n,i) (n&(1LL<<i))

#define ff first
#define ss second

#define SET(arr) memset(arr, -1, sizeof arr)
#define RESET(arr) memset(arr, 0, sizeof arr)

#define srt(v) sort(v.begin(), v.end())
#define uniq(v) v.resize(distance(v.begin(), unique(v.begin(), v.end())))
#define found(s,d) (s.find(d) != s.end())

#define FOR(i,s,e) for(LL i = s; i <= e; i++)
#define RFOR(i,e,s) for(LL i = e; i >= s; i--)

using namespace std;

const LL inf = 1e9;
const LL lim = 1010;

LL dp[lim][lim];

LL F(LL pos, LL rem, LL T, const vector<LL>& c, const vector<LL>& t) {
    if(rem < 0) return inf;
    if(pos == 0) {
        if(rem == T) return inf;
        else return 0;
    }
    LL &ret = dp[pos][rem];
    if(ret != -1) return ret;
    ret = min(F(pos-1, rem, T, c, t), c[pos] + F(pos-1, rem-t[pos], T, c, t));
    return ret;
}

LL baseline(LL N, LL T, const vector<LL>& c, const vector<LL>& t) {
    SET(dp);
    LL ans = F(N, T, T, c, t);
    if(ans >= inf) return -1; // Represents "TLE"
    else return ans;
}

vector<LL> generateInput(LL N) {
    vector<LL> c(N + 1), t(N + 1);
    for (LL i = 1; i <= N; i++) {
        c[i] = i;
        t[i] = i;
    }
    return {c, t};
}