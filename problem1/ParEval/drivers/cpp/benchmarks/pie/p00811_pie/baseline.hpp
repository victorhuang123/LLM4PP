#pragma once

#include<cmath>
#include<vector>
#include<algorithm>

#define pb push_back
#define rep(i,n) for(int i=0;i<n;i++)

using namespace std;

typedef vector<int> vi;

const double EPS=1e-9;

pair<int, int> baseline(int m, int a, int b) {
    static bool er[100000]={}; er[0]=er[1]=true;
    rep(i,400) if(!er[i]) for(int j=i*i;j<100000;j+=i) er[j]=true;

    vi pr;
    rep(i,100000) if(!er[i]) pr.pb(i);

    int popt=2,qopt=2;
    rep(i,pr.size()){
        int p=pr[i];
        if(p*p>m) continue;
        int q=*(upper_bound(pr.begin()+i,pr.end(),min(b*p/a,m/p))-1);
        if(popt*qopt<p*q) popt=p,qopt=q;
    }
    return make_pair(popt, qopt);
}