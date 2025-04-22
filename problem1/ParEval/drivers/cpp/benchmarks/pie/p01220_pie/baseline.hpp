#pragma once

#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>

using namespace std;

typedef complex<double> P;

const double eps = 1.0e-7;
const double pi = acos(-1);

bool equals(double a, double b) { return abs(a-b) < eps; }
bool equals(P a, P b) {
  return equals(a.real(),b.real()) && equals(a.imag(),b.imag());
}

namespace std {
  bool operator < (const P& a, const P& b) {
    if(!equals(a.real(),b.real())) return a.real() < b.real();
    if(!equals(a.imag(),b.imag())) return a.imag() < b.imag();
    return false;
  }
}

P rotate(P p, double rad) {
  return P(cos(rad)*p.real() - sin(rad)*p.imag(),
           sin(rad)*p.real() + cos(rad)*p.imag());
}

double baseline(int N) {
  const static double r2 = 1.0/(2.0*(1.0-cos(pi*2.0/3.0)));
  vector<P> ps;
  vector<P> tri;
  tri.push_back(P(1.0,0.0));
  tri.push_back(rotate(P(1.0,0.0),pi*2.0/3.0));
  tri.push_back(rotate(P(1.0,0.0),-pi*2.0/3.0));
  double d = pi*2.0/(double)N;
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < tri.size(); ++j) {
      ps.push_back(rotate(tri[j],pi*2.0*i/(double)N));
    }
  }

  sort(ps.begin(), ps.end());
  int n = ps.size();
  for(int i = 1; i < ps.size(); ++i)
    n -= equals(ps[i-1],ps[i]);

  double rad = pi*2.0/(double)n;
  double rad2 = (pi*(n-2)/(double)n - pi/3.0)/2.0;
  double l2 = 2.0 * r2 * (1.0-cos(rad));
  return r2*pi - n*( (rad-sin(rad))*r2/2.0 + tan(rad2)*l2/4.0 );
}