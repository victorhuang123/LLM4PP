#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define rep(n) for(int i=0;i<n;i+=1)
#define prarr(a,n) rep(n) cout<<a[i]<<endl printf("%s\n"," " );
#define sc(a) scanf("%d",&a);
#define scl(a) scanf("%lld",&a);
#define scf(a) ascanf("%f",&a);
#define fi first
#define se second
#define pu push_back
#define inf 1000000001
#define MOD 1000000007 
#define INF 100000000000001
const int MAXN = 2e5+10;

vector<int> baseline(int n, vector<pii>& a) {
    map<int,vector<int>> m;
    map<int,int> ans;
    vector<int> b(n, 0);

    rep(n) {
        a[i].se = i;
    }

    sort(a.begin(), a.end());

    rep(n) {
        if((i+1)<=n/2)
            ans[a[i].se] = a[n/2].fi;
        else
            ans[a[i].se] = a[n/2-1].fi;     
    }

    vector<int> result(n);
    rep(n) {
        result[i] = ans[i];
    }

    return result;
}

vector<pii> generateInput(int n) {
    vector<pii> a(n);
    rep(n) {
        a[i].fi = rand() % 1000000;
        a[i].se = i;
    }
    return a;
}