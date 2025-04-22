#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef long double louble;

template<typename T1,typename T2> inline T1 max(T1 a,T2 b){return a<b?b:a;}
template<typename T1,typename T2> inline T1 min(T1 a,T2 b){return a<b?a:b;}

const char lf = '\n';

namespace ae86 {
    const int bufl = 1 << 15;
    char buf[bufl],*s=buf,*t=buf;

    inline int fetch() {
        if(s==t){t=(s=buf)+fread(buf,1,bufl,stdin);if(s==t)return EOF;}
        return *s++;
    }

    inline int ty() {
        int a=0;int b=1,c=fetch();
        while(!isdigit(c))b^=c=='-',c=fetch();
        while(isdigit(c))a=a*10+c-48,c=fetch();
        return b?a:-a;
    }
}
using ae86::ty;

const int _ = 200007;

struct cxk {
    lint c0,c1;
    cxk(lint c0_=0,lint c1_=0){c0=c0_,c1=c1_;}
    friend cxk operator + (cxk a,cxk b){return cxk(a.c0+b.c0,a.c1+b.c1);}
    friend int operator < (cxk a,cxk b){return a.c1*b.c0<a.c0*b.c1;}
}ps[_];

int findbfa(int x, int bfa[]) {
    return x==bfa[x]?x:bfa[x]=findbfa(bfa[x], bfa);
}

lint baseline(int n, vector<int>& fa, vector<int>& val) {
    int bfa[_] = {0}, bval[_] = {0};
    set<pair<cxk,int>> s;

    for(int i=1;i<=n;i++)bfa[i]=i,ps[i]=cxk(val[i]==0,val[i]==1),s.emplace(ps[i],i);

    lint ans=0;
    while(!s.empty()) {
        int a=(*s.begin()).second;
        s.erase(s.begin());
        if(a==1)continue;
        int aa=findbfa(fa[a], bfa);
        bfa[a]=aa,ans+=ps[aa].c1*ps[a].c0,s.erase(make_pair(ps[aa],aa));
        ps[aa]=ps[aa]+ps[a],s.emplace(ps[aa],aa);
    }
    return ans;
}

vector<int> generateInput(int n) {
    vector<int> fa(n + 1), val(n + 1);
    for (int i = 1; i <= n; i++) {
        fa[i] = i - 1;
        val[i] = rand() % 2;
    }
    return {fa, val};
}