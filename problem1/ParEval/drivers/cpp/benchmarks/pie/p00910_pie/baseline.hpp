#pragma once

#include<bits/stdc++.h>

#define rep(i,n) for(int i=0;i<(int)(n);i++)

#define init(a) memset((a),0,sizeof(a))

using namespace std;

typedef double D;

typedef vector<D> P;

const D EPS = 1e-8;

D baseline(int n, int m, int r, const vector<P> &sp, const vector<D> &sr, const vector<P> &tp, const vector<D> &tb, const P &ep){
  vector<vector<int>> rm(m);
  rep(i,m)rep(j,n){
    P l = ep, r = tp[i];
    D r2 = sr[j]*sr[j];
    bool f1 = (dis2(sp[j],l)<r2+EPS), f2 = (dis2(sp[j],r)<r2+EPS);
    if(f1&&f2)rm[i].push_back(j);
    else if(f1||f2)rm[i].push_back(j);
    else {
      rep(k,30){
        P m1 = mul(add(mul(l,2),r),1.0/3), m2 = mul(add(l,mul(r,2)),1.0/3);
        D d1 = dis2(sp[j],m1), d2 = dis2(sp[j],m2);
        if(d1<d2)r = m2;
        else l = m1;
      }
      if(dis2(sp[j],l)<r2+EPS)rm[i].push_back(j);
    }
  }

  D res = 0.0;
  D p[20];
  rep(i,m)p[i] = tb[i]/dis2(ep,tp[i]);

  rep(bit,1<<m){
    int use[2020];
    init(use);
    D sum = 0.0;
    rep(i,m){
      if((bit>>i)&1){
        sum += p[i];
        rep(j,rm[i].size())use[rm[i][j]] = 1;
      }
    }
    if(accumulate(use,use+n,0)>r)continue;
    res = max(res,sum);
  }
  return res;
}

vector<P> generateInput(int n, int m) {
  vector<P> sp(n, P(3));
  vector<D> sr(n);
  vector<P> tp(m, P(3));
  vector<D> tb(m);
  P ep(3);

  rep(i, n) {
    sp[i][0] = rand() % 1000;
    sp[i][1] = rand() % 1000;
    sp[i][2] = rand() % 1000;
    sr[i] = rand() % 100;
  }

  rep(i, m) {
    tp[i][0] = rand() % 1000;
    tp[i][1] = rand() % 1000;
    tp[i][2] = rand() % 1000;
    tb[i] = rand() % 100;
  }

  ep[0] = rand() % 1000;
  ep[1] = rand() % 1000;
  ep[2] = rand() % 1000;

  return {sp, sr, tp, tb, ep};
}