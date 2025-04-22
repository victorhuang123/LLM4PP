#pragma once

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

int baseline(int n, int m, int k, const vector<pair<int, int>>& edges) {
    using P = pair<int, int>;
    map<P, int> idx;

    vector<vector<int>> G(n);
    for (int i = 0; i < m; i++) {
        int a = edges[i].first, b = edges[i].second;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
        idx[P(a, b)] = idx[P(b, a)] = i;
    }

    vector<int> uf(m);
    for (int i = 0; i < m; i++) uf[i] = i;

    function<int(int)> find = [&](int x) {
        return uf[x] == x ? x : uf[x] = find(uf[x]);
    };

    auto unite = [&](int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) uf[y] = x;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < (int)G[i].size(); j++) {
            unite(idx[P(i, G[i][0])], idx[P(i, G[i][j])]);
        }
    }

    vector<set<int>> cnt(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)G[i].size(); j++) {
            int p = G[i][j];
            cnt[find(idx[P(i, p)])].insert(i);
            cnt[find(idx[P(i, p)])].insert(p);
        }
    }

    auto gcd = [](int a, int b) {
        while (b) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    };

    auto pow = [](int base, int exp) {
        int result = 1;
        while (exp) {
            if (exp & 1) result *= base;
            base *= base;
            exp >>= 1;
        }
        return result;
    };

    auto calc1 = [&](int x) -> int {
        int res = 0;
        for (int i = 0; i < x; i++)
            res += pow(k, gcd(i, x));
        return res / x;
    };

    auto H = [&](int k, int n) -> int {
        return pow(k, n);
    };

    int ans = 1;
    for (int i = 0; i < m; i++) {
        if (find(i) != i) continue;
        if (uf[i] < (int)cnt[i].size()) ans *= pow(k, uf[i]);
        if (uf[i] == (int)cnt[i].size()) ans *= calc1(uf[i]);
        if (uf[i] > (int)cnt[i].size()) ans *= H(k, uf[i]);
    }

    return ans;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        edges.push_back({a, b});
    }
    return edges;
}