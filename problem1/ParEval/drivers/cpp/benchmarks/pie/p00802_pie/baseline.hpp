#pragma once

#include <vector>
#include <cmath>
#include <complex>
#include <algorithm>

using namespace std;

typedef complex<double> P;

const double PI = 3.1415926535;

inline double outp(const P &a, const P &b){
  return (conj(a)*b).imag();
}

double solve(int p, int rest, int n, int m, int fst, const vector<P> &pos, vector<vector<double>> &memo){
  if(p == n) return 0.0;
  if(rest == 0) return 0.0;
  if(memo[p][rest] > -1.0)
    return memo[p][rest];
  double ret = 0.0;

  for(int i = p + 1; i < n; i++){
    double tmp = 0.0;

    if(rest != m - 1){
      P p1 = pos[fst];
      P p2 = pos[p];
      P p3 = pos[i];
      tmp += std::abs(outp(p2 - p1, p3 - p1) / 2.0);
    }

    ret = max(ret, tmp + solve(i, rest - 1, n, m, fst, pos, memo));
  }

  return memo[p][rest] = ret;
}

double baseline(int n, int m, const vector<double> &angles){
  vector<P> pos(n);
  for(int i = 0; i < n; i++){
    pos[i] = P(cos(2 * PI * angles[i]), sin(2 * PI * angles[i]));
  }

  double ans = 0.0;
  for(int i = 0; i < n; i++){
    vector<vector<double>> memo(n, vector<double>(m, -2.0));
    int fst = i;
    ans = max(ans, solve(i, m - 1, n, m, fst, pos, memo));
  }

  return ans;
}

vector<double> generateInput(int n){
    vector<double> angles(n);
    for(int i = 0; i < n; i++){
        angles[i] = static_cast<double>(i) / n;
    }
    return angles;
}