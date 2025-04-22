#pragma once

#include<bits/stdc++.h>

using namespace std;

#define maxn 200008

vector<pair<int, int>> generateInput(int n, int m, int q) {
    vector<pair<int, int>> edges(m);
    vector<pair<int, int>> queries(q);

    for(int i = 0; i < m; i++) {
        edges[i] = {rand() % n + 1, rand() % n + 1};
    }

    for(int i = 0; i < q; i++) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        if(a > b) swap(a, b);
        queries[i] = {a, b};
    }

    return edges;
}

int baseline(int n, int m, int q, vector<pair<int, int>>& edges, vector<pair<int, int>>& queries) {
    vector<int> v1[maxn];

    for(int i = 0; i < m; i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        v1[a].push_back(b);
    }

    for(int i = 1; i <= n; i++) {
        sort(v1[i].begin(), v1[i].end());
    }

    int total = 0;

    for(int i = 0; i < q; i++) {
        int a = queries[i].first;
        int b = queries[i].second;
        int ans = 0;

        for(int j = a; j <= b; j++) {
            ans += upper_bound(v1[j].begin(), v1[j].end(), b) - v1[j].begin();
        }

        total += ans;
    }

    return total;
}