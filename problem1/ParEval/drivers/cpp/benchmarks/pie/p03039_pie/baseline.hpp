#pragma once

#include <vector>
#include <cmath>

using namespace std;

int baseline(int n, int m, long long k, int MOD) {
  const int MAT[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 4, 10},
    {0, 1, 8, 25, 56},
    {0, 4, 25, 72, 154},
    {0, 10, 56, 154, 320}
  };

  const int N = 2e5 + 10;
  vector<int> t1(N), t2(N);

  auto fpow = [&](int a, int b) {
    int ans = 1;
    for(; b > 0; b >>= 1, a = 1ll * a * a % MOD) {
      if(b & 1) {
        ans = 1ll * ans * a % MOD;
      }
    }
    return ans;
  };

  auto fac = [&](int n) {
    if(n <= 1) return 1;
    const int C = sqrt(n);
    vector<int> v(C);
    for(int i = 0; i < C; i++) {
      v[i] = MOD - (i + 1);
    }
    vector<int> p(C);
    for(int i = 0; i < C; i++) {
      p[i] = C * i;
    }
    int ans = 1;
    for(int i = 0; i < C; i++) {
      ans = 1ll * ans * p[i] % MOD;
    }
    for(int i = C * C + 1; i <= n; i++) {
      ans = 1ll * ans * i % MOD;
    }
    return ans;
  };

  auto C = [&](int n, int m) {
    return 1ll * fac(n) * fpow(fac(n - m), MOD - 2) % MOD * fpow(fac(m), MOD - 2) % MOD;
  };

  auto lucas = [&](long long n, long long m) {
    if(n < MOD && m < MOD) {
      return C(n, m);
    }
    return 1ll * C(n % MOD, m % MOD) * lucas(n / MOD, m / MOD) % MOD;
  };

  for(int i = 1; i <= 4; i++) {
    for(int j = 1; j <= 4; j++) {
      t1[j] = MAT[i][j];
    }
    for(int j = 5; j <= n; j++) {
      t1[j] = (((4ll * t1[j - 1] - 6ll * t1[j - 2] + 4ll * t1[j - 3] - 1ll * t1[j - 4]) % MOD) + MOD) % MOD;
    }
    t2[i] = t1[n];
  }
  for(int i = 5; i <= m; i++) {
    t2[i] = (((4ll * t2[i - 1] - 6ll * t2[i - 2] + 4ll * t2[i - 3] - 1ll * t2[i - 4]) % MOD) + MOD) % MOD;
  }
  return 1ll * t2[m] * lucas(1ll * n * m - 2, k - 2) % MOD;
}

vector<int> generateInput() {
  return {200000, 200000, 1000000000000LL, 1000000007};
}