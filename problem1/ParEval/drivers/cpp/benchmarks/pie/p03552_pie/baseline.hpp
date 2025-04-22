#pragma once

#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(ll i=0; i<(ll)(n); i++)
#define FOR(i,n,m) for (ll i=n; i<(ll)(m); i++)
#define pb push_back
#define INF 1000000007LL
#define all(a) (a).begin(),(a).end()
#define chmin(a,b) a=min(a,b)
#define chmax(a,b) a=max(a,b)

typedef long long ll;
typedef pair<int,int> p;

int dy[4]={-1,1,0,0};
int dx[4]={0,0,1,-1};

int baseline(int N, int Z, int W, vector<int>& a) {
    map<int, int> dp[2][2010];
    function<int(int, bool, int, int)> score = [&](int used, bool turn, int x, int y) {
        if (used == N) return abs(x - y);
        if (turn) {
            if (dp[turn][used].count(x)) return dp[turn][used][x];
            int res = INF;
            FOR(i, used + 1, N+1) {
                res = min(res, score(i, turn^1, x, a[i-1]));
            }
            return dp[turn][used][x] = res;
        } else {
            if (dp[turn][used].count(y)) return dp[turn][used][y];
            int res = 0;
            FOR(i, used + 1, N+1) {
                res = max(res, score(i, turn^1, a[i-1], y));
            }
            return dp[turn][used][y] = res;
        }
    };
    return score(0, 0, Z, W);
}

vector<int> generateInput(int N) {
    vector<int> a(N);
    REP(i, N) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}