#pragma once

#include<bits/stdc++.h>

using namespace std;

void baseline(int n, long long m, int q, vector<tuple<int, int, int>>& edges) {
   int cc = n;
   vector<pair<int, int>> zero, one;
   for (auto& edge : edges) {
      int u = get<0>(edge), v = get<1>(edge), c = get<2>(edge);
      if (c) {
         one.emplace_back(u, v);
      } else {
         zero.emplace_back(u, v);
      }
   }
   vector<int> p(n), sz(n, 1);
   iota(p.begin(), p.end(), 0);
   auto f = [&](int u) {
      return p[u] = (p[u] == u ? u : f(p[u]));
   };
   auto unite = [&](int u, int v) {
      u = f(u);
      v = f(v);
      if(u == v) return false;
      cc--;
      if(sz[v] < sz[u]) swap(u, v);
      p[u] = v;
      sz[v] += sz[u];
      return true;
   };
   for (auto& e : zero) {
      int u = e.first, v = e.second;
      if (unite(u, v)) m--;
   }
   vector<int> pr(n, -1);
   for (int i = 0; i < n; ++i)
      pr[i] = f(i);
   bool need = false;
   for (auto& e : one) {
      int u = pr[e.first], v = pr[e.second];
      if (u == v || cc <= 2) {
         return "No";
      }
      need = true;
   }
   if (!need) {
      long long canAdd = 1ll * cc * (cc - 1) / 2;
      return (m >= (cc - 1) && m <= canAdd) ? "Yes" : "No";
   }
   set<pair<int, int>> s;
   for (int i = 0; i < n; ++i) {
      int theone = pr[i];
      s.insert({theone, sz[theone]});
   }
   m -= ((int)s.size());
   long long rem = 1ll * cc * (cc - 1) / 2;
   rem -= (int)s.size();
   return (m < 0 || m > rem) ? "No" : "Yes";
}

vector<tuple<int, int, int>> generateInput(int n, int q) {
   vector<tuple<int, int, int>> edges;
   for (int i = 0; i < q; ++i) {
      int u = rand() % n;
      int v = rand() % n;
      int c = rand() % 2;
      edges.emplace_back(u, v, c);
   }
   return edges;
}