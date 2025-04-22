#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<int, int>> generateInput(int N, int M) {
    vector<pair<int, int>> edges;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            edges.push_back({i, j + N});
        }
    }
    return edges;
}

vector<int> baseline(int N, int M, vector<pair<int, int>>& edges) {
    vector<int> IE[100001];
    int num = 1;
    int topo[100001], jisuu[100001] = {};

    for (int i = 0; i < N + M - 1; i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        IE[b].push_back(a);
        jisuu[a]++;
    }

    stack<int> ST;
    for (int i = 1; i <= N; i++) {
        if(!jisuu[i]) ST.push(i);
    }

    while (ST.size()) {
        int k = ST.top();
        ST.pop();
        topo[k] = num++;
        for (int u : IE[k]) {
            jisuu[u]--;
            if (!jisuu[u]) ST.push(u);
        }
    }

    vector<int> result;
    for (int i = 1; i <= N; i++) {
        int kotae = 0;
        int saishou = 1e9;
        if (topo[i] == N) kotae = 0;
        else {
            for (int u : IE[i]) {
                if (saishou > topo[u]) {
                    saishou = topo[u];
                    kotae = u;
                }
            }
        }
        result.push_back(kotae);
    }
    return result;
}