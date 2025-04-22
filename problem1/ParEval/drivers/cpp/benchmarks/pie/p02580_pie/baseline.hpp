#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int INF = 0x3f3f3f3f;

const LL mod = 1e9 + 7;

const int N = 300005;

int val[N << 2];

void update(int u, int l, int r, int x, int v) {
    if (l == r) {
        val[u] += v;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid)
        update(u << 1, l, mid, x, v);
    else
        update(u << 1 | 1, mid + 1, r, x, v);
    val[u] = max(val[u << 1], val[u << 1 | 1]);
}

int baseline(int n, int m, int g, vector<pair<int, int>>& queries) {
    vector<int> a(n + 1, 0);
    vector<vector<int>> G(n + 1);

    for (int i = 0; i < g; i++) {
        int x = queries[i].first, y = queries[i].second;
        a[x]++;
        update(1, 1, m, y, 1);
        G[x].push_back(y);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (auto y : G[i]) update(1, 1, m, y, -1);
        ans = max(ans, a[i] + val[1]);
        for (auto y : G[i]) update(1, 1, m, y, 1);
    }
    return ans;
}

vector<pair<int, int>> generateInput(int n, int m, int g) {
    vector<pair<int, int>> queries(g);
    for (int i = 0; i < g; i++) {
        queries[i] = {rand() % n + 1, rand() % m + 1};
    }
    return queries;
}