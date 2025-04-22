#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> generateInput(int n) {
    vector<int> parents(n - 1);
    vector<int> values(n);
    for (int i = 0; i < n - 1; ++i) {
        parents[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        values[i] = i;
    }
    return {parents, values};
}

vector<int> baseline(int n, const vector<int>& parents, const vector<int>& values) {
    vector<int> ans;
    vector<int> p(n), where(n), a(n), blocked(n);
    vector<vector<int>> edges(n);

    for (int i = 1; i < n; i++) {
        p[i] = parents[i-1];
        edges[p[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        a[i] = values[i];
        where[a[i]] = i;
    }
    for (int i = 0; i < n; i++) blocked[i] = false;

    auto getdown = [&](int v, int value, auto&& getdown) -> pair<int, int> {
        pair<int, int> mx = make_pair(-1, 0);
        for (int to : edges[v]) {
            if (blocked[to]) continue;
            pair<int, int> got = getdown(to, value, getdown);
            if (got.first < 0) continue;
            if (mx.first < 0 || a[mx.second] < a[got.second]) {
                mx = got;
            }
        }
        if (mx.first < 0 && a[v] > value) {
            mx = make_pair(v, v);
        }
        if (a[v] > a[mx.second])
            mx.second = v;
        return mx;
    };

    auto shift = [&](int start) {
        int v = start;
        int tmp = a[v];
        while (v != 0) {
            v = p[v];
            int ntmp = a[v];
            a[v] = tmp;
            where[a[v]] = v;
            tmp = ntmp;
        }
        a[start] = tmp;
        where[a[start]] = start;
        ans.push_back(start);
    };

    int cur = n - 1;
    while (cur >= 0) {
        while (a[0] != cur) {
            int v = where[cur];
            int u = getdown(v, a[0], getdown).first;
            shift(u);
        }
        shift(cur);
        blocked[cur] = true;
        --cur;
    }

    return ans;
}