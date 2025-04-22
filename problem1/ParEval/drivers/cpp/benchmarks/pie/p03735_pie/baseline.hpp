#pragma once

#include <bits/stdc++.h>

using namespace std;

#define ll long long

#define REP(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)

#define DREP(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)

#define EREP(i,a) for(int i=start[(a)];i;i=e[i].next)

template<class T>inline void chkmax(T &a,T b){ if(a<b)a=b;}

template<class T>inline void chkmin(T &a,T b){ if(a>b)a=b;}

#define fi first

#define se second

#define mkr(a,b) make_pair(a,b)

#define pii pair<ll,ll>

const int maxn=4e5+20;

pii a[maxn];

ll baseline(int n, vector<int>& x, vector<int>& y) {
    REP(i,1,n) a[i*2-1]=mkr(x[i],i), a[i*2]=mkr(y[i],i);
    REP(i,1,n) if(x[i]>y[i]) swap(x[i],y[i]);
    sort(a+1,a+n*2+1);

    ll Ans=1ll<<60;
    int vis[maxn];

    if(a[1].se!=a[n*2].se) {
        memset(vis,0,sizeof(vis));
        ll L,R;
        vis[a[n*2].se]++;
        REP(i,1,n*2-1) {
            if(!vis[a[i].se]) vis[a[i].se]++;
            else { L=i; break; }
        }
        memset(vis,0,sizeof(vis));
        vis[a[1].se]++;
        DREP(i,n*2,1) {
            if(!vis[a[i].se]) vis[a[i].se]++;
            else { R=a[i].fi; break; }
        }
        memset(vis,0,sizeof(vis));
        REP(i,2,L) {
            chkmin(Ans,1ll*(a[n*2].fi-a[1].fi)*(R-a[i].fi));
            chkmax(R,(ll)y[a[i].se]);
        }
    }

    ll mn1=1ll<<60, mx1=0, mn2=1ll<<60, mx2=0;
    memset(vis,0,sizeof(vis));
    REP(i,1,n*2) {
        if(!vis[a[i].se]) vis[a[i].se]++, chkmin(mn1,a[i].fi), chkmax(mx1,a[i].fi);
        else chkmin(mn2,a[i].fi), chkmax(mx2,a[i].fi);
    }
    chkmin(Ans,1ll*(mx2-mn2)*(mx1-mn1));
    return Ans;
}

vector<int> generateInput(int n) {
    vector<int> x(n+1), y(n+1);
    REP(i,1,n) {
        x[i] = rand() % 1000000;
        y[i] = rand() % 1000000;
    }
    return x, y;
}