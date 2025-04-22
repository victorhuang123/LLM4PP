#pragma once

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int baseline(int n, int m, vector<pair<int, int>>& ab, vector<pair<int, int>>& lr) {
    vector<int> h(N * 2, -1), ne(N * 2), e(N * 2), w(N * 2), vis(N), use(N);
    vector<int> a(N), b(N), c(N), d(N);
    int idx = 0;

    for (int i = 1; i <= n; i++) {
        a[i] = ab[i - 1].first;
        b[i] = ab[i - 1].second;
        d[i] = a[i];
    }

    sort(d.begin() + 1, d.begin() + n + 1);

    auto get = [&](int x) {
        return lower_bound(d.begin() + 1, d.begin() + n + 1, x) - d.begin();
    };

    for (int i = 1; i <= n; i++)
        c[get(a[i])] = b[i];

    for (int i = n + 1; i >= 1; i--) c[i] ^= c[i - 1];

    auto add = [&](int a, int b, int c) {
        e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
    };

    for (int i = 1; i <= m; i++) {
        int l = lr[i - 1].first;
        int r = lr[i - 1].second;
        l = get(l);
        r = upper_bound(d.begin() + 1, d.begin() + n + 1, r) - d.begin() - 1;
        if (l <= r)
            add(l, r + 1, i), add(r + 1, l, i);
    }

    function<int(int)> dfs = [&](int u) {
        vis[u] = 1;
        int x = c[u];
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (!vis[v] && dfs(v))
                x ^= 1, use[w[i]] = 1;
        }
        return x;
    };

    for (int i = 1; i <= n + 1; i++)
        if (!vis[i] && dfs(i)) {
            return -1;
        }

    int ans = 0;
    for (int i = 1; i <= m; i++)
        if (use[i]) ans++;

    return ans;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> ab(n), lr(m);
    for (int i = 0; i < n; i++) {
        ab[i] = {rand() % N, rand() % 2};
    }
    for (int i = 0; i < m; i++) {
        int l = rand() % N;
        int r = l + rand() % (N - l);
        lr[i] = {l, r};
    }
    return ab, lr;
}