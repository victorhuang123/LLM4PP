#pragma once

#include <bits/stdc++.h>

using namespace std;

#define ALL(x) (x).begin(),(x).end()
#define REP(i, n) for(int i=0;i<n;i++)
using P = pair<int,int>;
using V = vector<int>;
const int INF = 1e9;

vector<P> baseline(int n, vector<int>& a) {
  int mx = -INF, mn = INF;
  REP(i,n) {
    mx = max(mx, a[i]);
    mn = min(mn, a[i]);
  }
  int add = abs(mx) >= abs(mn) ? mx : mn;
  int add_idx = 0;
  REP(i,n) {
    if (a[i] == add) { add_idx = i; break; }
  }

  vector<P> ans;
  REP(i,n) {
    ans.push_back({ add_idx, i });
  }
  if (add >= 0) {
    REP(i,n-1) ans.push_back({ i, i+1 });
  } else {
    REP(i,n-1) ans.push_back({ n-i-1, n-i-2 });
  }

  return ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    REP(i, n) {
        a[i] = (i % 2 == 0) ? i : -i;
    }
    return a;
}