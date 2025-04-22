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

ll cnt[15];
map < pii , bool > flag;
int dy[] = {-2,-2,-2,-1,-1,-1,0,0,0};
int dx[] = {-2,-1,0,-2,-1,0,-2,-1,0};

bool inRange(int y, int x, int h, int w){
    return y > 0 && y <= h && x > 0 && x <= w;
}

int getCnt(int ty, int tx, int ny, int nx){
    int ret = 0;
    REP(i,ty,ny){
        REP(j,tx,nx){
            if(flag[MP(i,j)]) ret++;
        }
    }
    return ret;
}

void update(int y, int x, int h, int w){
    FOR(i,9){
        int ty = y + dy[i];
        int tx = x + dx[i];
        int ny = ty + 2;
        int nx = tx + 2;
        if(inRange(ty,tx,h,w) && inRange(ny,nx,h,w)){
            int bef = getCnt(ty,tx,ny,nx);
            cnt[bef]--;
            cnt[bef+1]++;
        }
    }
    flag[MP(y,x)] = true;
}

vector<ll> baseline(int h, int w, int n, vii& points){
    cnt[0] = (h-2) * (w - 2);
    FOR(i,n){
        int y = points[i].FI;
        int x = points[i].SE;
        update(y,x,h,w);
    }
    vector<ll> result(10);
    FOR(i,10) result[i] = cnt[i];
    return result;
}

vii generateInput(int h, int w, int n){
    vii points(n);
    FOR(i,n){
        points[i].FI = rand() % h + 1;
        points[i].SE = rand() % w + 1;
    }
    return points;
}