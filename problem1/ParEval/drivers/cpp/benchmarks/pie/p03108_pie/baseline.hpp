#pragma once

#include <bits/stdc++.h>
using namespace std;

vector<long long> baseline(int n, int m, vector<pair<int, int>>& edgs) {
    reverse(edgs.begin(), edgs.end());
    vector<int> par(n + 1), rnk(n + 1, 1);
    for (int i = 1; i <= n; ++i) par[i] = i;

    auto findpar = [&](int u) {
        return par[u] = (u == par[u] ? u : findpar(par[u]));
    };

    vector<long long> ans(m);
    ans[0] = (1ll * n * (n - 1) / 2);

    for (int i = 0; i < m - 1; ++i) {
        int u = findpar(edgs[i].first);
        int v = findpar(edgs[i].second);
        if (u == v) {
            ans[i + 1] = ans[i];
            continue;
        }
        long long ret = 1ll * rnk[u] * rnk[v];
        if (rnk[u] < rnk[v]) swap(u, v);
        par[v] = u;
        rnk[u] += rnk[v];
        ans[i + 1] = ans[i] - ret;
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edgs(m);
    for (int i = 0; i < m; ++i) {
        edgs[i] = {rand() % n + 1, rand() % n + 1};
    }
    return edgs;
}