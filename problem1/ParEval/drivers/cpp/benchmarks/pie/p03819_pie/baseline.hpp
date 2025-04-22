#pragma once

#include <vector>
#include <utility>

using namespace std;

#define M 400010

inline int Lowbit(int x) { return x & (-x); }

void Add(int x, int v, vector<int>& c, int m) {
    while (x <= m) {
        c[x] += v;
        x += Lowbit(x);
    }
}

int Val(int x, vector<int>& c) {
    int res = 0;
    while (x) {
        res += c[x];
        x -= Lowbit(x);
    }
    return res;
}

vector<int> baseline(int n, int m, vector<vector<pair<int, int>>>& g) {
    vector<int> c(M, 0);
    vector<int> result;
    int sz = 0;

    for (int i = 1; i <= m; i++) {
        int x = i, res = 0;
        do {
            res += Val(x, c);
            x += i;
        } while (x <= m);

        for (const auto& p : g[i]) {
            Add(p.first, 1, c, m);
            Add(p.second + 1, -1, c, m);
        }
        result.push_back(res + n - sz);
        sz += g[i].size();
    }

    return result;
}

vector<vector<pair<int, int>>> generateInput(int n, int m) {
    vector<vector<pair<int, int>>> g(m + 1);
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < n; j++) {
            g[i].emplace_back(j + 1, j + 1);
        }
    }
    return g;
}