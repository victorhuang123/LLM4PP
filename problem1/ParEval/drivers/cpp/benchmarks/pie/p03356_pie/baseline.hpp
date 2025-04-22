#pragma once

#include <bits/stdc++.h>
using namespace std;

int baseline(int n, int k, vector<int>& a, vector<pair<int, int>>& edges) {
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) p[i] = i;

    function<int(int)> find = [&](int x) {
        if (x == p[x]) return x;
        return p[x] = find(p[x]);
    };

    for (int i = 0; i < k; i++) {
        int u = edges[i].first, v = edges[i].second;
        u = find(u), v = find(v);
        p[u] = v;
    }

    int t = 0;
    vector<set<int>> s(n + 1);
    for (int i = 1; i <= n; i++) {
        find(i);
        if (s[p[i]].find(i) != s[p[i]].end()) {
            t++;
        } else {
            s[p[i]].insert(i);
        }
        if (s[p[i]].find(a[i]) != s[p[i]].end()) {
            t++;
        } else {
            s[p[i]].insert(a[i]);
        }
    }
    return t;
}

vector<int> generateInputA(int n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = rand() % n + 1;
    }
    return a;
}

vector<pair<int, int>> generateInputEdges(int n, int k) {
    vector<pair<int, int>> edges(k);
    for (int i = 0; i < k; i++) {
        int u = rand() % n + 1;
        int v = rand() % n + 1;
        edges[i] = {u, v};
    }
    return edges;
}