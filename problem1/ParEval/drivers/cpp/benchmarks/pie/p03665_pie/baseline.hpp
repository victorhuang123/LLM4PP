#pragma once

#include <bits/stdc++.h>

using namespace std;

#define EACH(i,a) for (auto& i : a)
#define FOR(i,a,b) for(int i=(int)a;i<(int)b;++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(a) (a).begin(),(a).end()

typedef long long ll;

const int INF = 1e9 + 1;
const int MOD = 1e9 + 7;
const int MAX_N = 1e3 + 1;

ll memo[MAX_N][MAX_N];

ll nCr(ll n, ll r) {
  if (r == 0 || n == r) return 1;
  if (memo[n][r] >= 0) return memo[n][r];
  return memo[n][r] = nCr(n - 1, r - 1) + nCr(n - 1, r);
}

ll baseline(int N, int P, const vector<int>& a) {
  int odd = 0, even = 0;
  memset(memo, -1, sizeof(memo));

  EACH(i, a) {
    if (i & 1) odd++;
    else even++;
  }

  ll ans = 0ll;

  REP(i, odd + 1) {
    if (i % 2 == P) {
      ans += nCr(odd, i);
    }
  }
  REP(i, even) {
    ans *= 2;
  }

  return ans;
}

vector<int> generateInput(int N) {
    return vector<int>(N, 1);
}