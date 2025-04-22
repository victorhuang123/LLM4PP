#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

int d = 0;
int D[10002];
int topo[10002];
vector<int> E[10002];

void dfs(int A, int B) {
    if (!D[A]) {
        D[A] = B;
        topo[A] = d;
        d++;
        for (int i : E[A]) {
            dfs(i, B + 1);
        }
    }
}

int baseline(int N, vector<pair<int, int>>& edges, vector<int>& C) {
    rep(i, N - 1) {
        int a = edges[i].first;
        int b = edges[i].second;
        E[a].pb(b);
        E[b].pb(a);
    }

    int goukei = 0;
    int saidai = 0;
    rep(i, N) {
        goukei += C[i];
        saidai = max(saidai, C[i]);
    }
    sort(C.begin(), C.end());
    reverse(C.begin(), C.end());

    dfs(1, 1);
    return goukei - saidai;
}

vector<pair<int, int>> generateEdges(int N) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= N; i++) {
        edges.pb(mp(i / 2, i));
    }
    return edges;
}

vector<int> generateC(int N) {
    vector<int> C(N);
    for (int i = 0; i < N; i++) {
        C[i] = rand() % 1000000 + 1;
    }
    return C;
}