#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll solve(ll n, ll a, ll b, ll m) {
  if (b == 0) return n * (a / m);
  if (a >= m) return n * (a / m) + solve(n, a % m, b, m);
  if (b >= m) return n * (n - 1) / 2 * (b / m) + solve(n, a, b % m, m);
  return solve((a + b * n) / m, (a + b * n) % m, m, b);
}

pair<long long, long long> GetKBest(int k, long long cx, long long cy) {
  long long low = 0, high = 1;
  while (true) {
    long long cnt = solve(high / cx + 1, high % cx, cx, cy) + (high / cx + 1);
    if (cnt >= k) {
      break;
    }
    low = high + 1;
    high = 2 * high;
  }
  while (low < high) {
    long long mid = (low + high) >> 1;
    long long cnt = solve(mid / cx + 1, mid % cx, cx, cy) + (mid / cx + 1);
    if (cnt >= k) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  long long sx = 0, sy = 0;
  for (int x = 0; x * cx <= high; x++) {
    long long cc = (high - x * cx) / cy + 1;
    sx += cc * x;
    sy += cc * (cc - 1) / 2;
  }
  return {sx, sy};
}

bool Solvable(int k, int X, int Y) {
  auto a = make_pair(-1LL, -1LL), b = a;
  long long total = (long long) 1e9 + 7;
  long long low = 0, high = total;
  while (low < high) {
    long long mid = (low + high) >> 1;
    auto p = GetKBest(k, total - mid, mid);
    if (p.first <= X && p.second <= Y) {
      return true;
    }
    if (p.first >= X && p.second >= Y) {
      return false;
    }
    if (p.first < X) {
      a = p;
      low = mid + 1;
    } else {
      b = p;
      high = mid;
    }
  }
  return (a.second * (b.first - X) + b.second * (X - a.first) <= Y * (b.first - a.first));
}

int baseline(int X, int Y) {
  if (X > Y) {
    swap(X, Y);
  }
  int low = 3, high = (int) 2e6;
  while (low < high) {
    int mid = (low + high + 1) >> 1;
    if (Solvable(mid, X, Y)) {
      low = mid;
    } else {
      high = mid - 1;
    }
  }
  return low - 1;
}

pair<int, int> generateInput() {
  return {2000000, 2000000};
}