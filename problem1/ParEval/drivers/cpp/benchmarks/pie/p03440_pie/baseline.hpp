#pragma once

#include <bits/stdc++.h>

typedef long long LL;

LL baseline(int n, int m, std::vector<int>& w, std::vector<std::pair<int, int>>& edges) {
    std::multiset<int> st[n];
    std::set<std::pair<int, int>> spec;

    int fa[n], part = n;

    auto Find = [&](int x) {
        return fa[x] == x ? x : fa[x] = Find(fa[x]);
    };

    auto merge = [&](int u, int v) {
        if (Find(u) == Find(v)) return;
        if (st[fa[u]].size() > st[fa[v]].size()) std::swap(u, v);
        --part;
        for (int i: st[fa[u]]) {
            st[fa[v]].insert(i);
        }
        st[fa[u]].clear();
        if (!st[fa[v]].empty()) spec.insert(std::make_pair(st[fa[v]].size(), fa[v]));
        fa[fa[u]] = fa[v];
    };

    for (int i = 0; i < n; ++i) {
        fa[i] = i;
        st[i].insert(w[i]);
        spec.insert(std::make_pair(1, i));
    }

    for (const auto& edge : edges) {
        int u = edge.first, v = edge.second;
        spec.erase(spec.find(std::make_pair(st[Find(u)].size(), Find(u))));
        spec.erase(spec.find(std::make_pair(st[Find(v)].size(), Find(v))));
        merge(u, v);
    }

    LL ans = 0;

    while (part > 1) {
        if (spec.size() < 2) {
            return -1;
        }
        auto x = *--spec.end();
        spec.erase(--spec.end());

        auto y = *--spec.end();
        spec.erase(--spec.end());

        int u = x.second, v = y.second;
        ans += *st[Find(u)].begin() + *st[Find(v)].begin();

        st[Find(u)].erase(st[Find(u)].begin());
        st[Find(v)].erase(st[Find(v)].begin());

        merge(u, v);
    }

    return ans;
}

std::tuple<int, int, std::vector<int>, std::vector<std::pair<int, int>>> generate_input() {
    int n = 1e5, m = 2e5;
    std::vector<int> w(n);
    std::vector<std::pair<int, int>> edges(m);

    for (int i = 0; i < n; ++i) {
        w[i] = rand() % 1000000 + 1;
    }

    for (int i = 0; i < m; ++i) {
        int u = rand() % n;
        int v = rand() % n;
        edges[i] = std::make_pair(u, v);
    }

    return std::make_tuple(n, m, w, edges);
}