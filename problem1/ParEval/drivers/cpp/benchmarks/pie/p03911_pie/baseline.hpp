#pragma once

#include <bits/stdc++.h>

using namespace std;

using VI = vector<int>;

const int N = 2e5 + 100;

VI val[N];

struct DSU {
  VI sz, par;

  DSU(int n) {
    par.resize(n);
    iota(par.begin(), par.end(), 0);
    sz.resize(n, 1);
  }

  int find(int u) {
    if (par[u] == u) return u;
    return par[u] = find(par[u]);
  }

  void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) {
      par[u] = v;
      sz[v] += sz[u];
    }
  }

  int get(int u) {
    return sz[find(u)];
  }
};

string baseline(int n, int m, const vector<vector<int>>& input) {
  for (int i = 0; i < n; i++) {
    int sz = input[i][0];
    for (int j = 1; j <= sz; j++) {
      int x = input[i][j];
      val[x].push_back(i);
    }
  }

  DSU dsu(N + 100);

  for (int x = 1; x <= m; x++) {
    for (int i : val[x]) {
      dsu.merge(i, val[x][0]);
    }
  }

  if (dsu.get(0) == n) {
    return "YES";
  } else {
    return "NO";
  }
}

vector<vector<int>> generateInput(int n, int m) {
  vector<vector<int>> input(n);
  for (int i = 0; i < n; i++) {
    input[i].push_back(100);
    for (int j = 1; j <= 100; j++) {
      input[i].push_back(j);
    }
  }
  return input;
}