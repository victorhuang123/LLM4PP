#pragma once

#include<bits/stdc++.h>

using namespace std;

#define REPP(i,a,b,c) for(int i=a; i<=b; i+=c)
#define REP(i,a,b) REPP(i,a,b,1)
#define REVV(i,a,b,c) for(int i=a; i>=b; i-=c)
#define REV(i,a,b) REVV(i,a,b,1)
#define FOR(i,a) REP(i,0,(int)a-1)
#define FORD(i,a) REV(i,(int)a-1,0)
#define PB push_back
#define POB pop_back
#define MP make_pair
#define FI first
#define SE second

typedef long long ll;
typedef unsigned long long ull;
typedef pair < int , int > pii;
typedef vector < int > vi;
typedef vector < pii > vii;
typedef vector < ll > vl;

const double EPS = 1e-9;
const double PI = acos(-1);
const int INF = 1e9;
const ll MOD = 1e9 + 7;

ll addMod(ll a, ll b){
    return (a+b) % MOD;
}

ll mulMod(ll a, ll b){
    return (a*b) % MOD;
}

ll fast(ll a, ll b){
    if(b == 0) return 1;
    ll tmp = fast(a,b/2);
    tmp = mulMod(tmp, tmp);
    if(b & 1) tmp = mulMod(tmp, a);
    return tmp;
}

const int N = 2e5;

ll baseline(int n, const vector<int>& input) {
    int m = 0;
    int arr[N + 5];
    vi lst[N + 5];
    ll dp[N + 5];
    int nxt[N + 5];
    memset(nxt, -1, sizeof nxt);
    memset(dp, -1, sizeof dp);

    int bef = -1;
    REP(i, 1, n) {
        int x = input[i-1];
        if(x != bef) {
            arr[++m] = x;
            bef = x;
            lst[x].PB(m);
        }
    }

    REP(i, 1, N) {
        if(lst[i].size() > 1) {
            FOR(j, lst[i].size()-1) {
                nxt[lst[i][j]] = lst[i][j+1];
            }
        }
    }

    function<ll(int)> solve = [&](int idx) -> ll {
        if(idx == m+1) return 1;
        ll& ret = dp[idx];
        if(ret != -1) return ret;
        ret = solve(idx+1);
        if(nxt[idx] != -1) ret = addMod(ret, solve(nxt[idx]));
        return ret;
    };

    return solve(1);
}

vector<int> generateInput(int n) {
    vector<int> input(n);
    for (int i = 0; i < n; ++i) {
        input[i] = rand() % N + 1;
    }
    return input;
}