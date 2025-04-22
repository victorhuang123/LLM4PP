#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

int baseline(int N, int K, vector<int>& parents) {
    int kotae = 0;
    vector<int> E[100001];

    rep1(i, N) {
        int a = parents[i - 1];
        if (i != 1) E[a].pb(i);
        else if (a != 1) kotae++;
    }

    function<int(int, int)> dfs = [&](int A, int D) {
        int d = 1;
        for (int to : E[A]) {
            d = max(d, dfs(to, D + 1) + 1);
        }
        if (d >= K && D > 1) {
            kotae++;
            return 0;
        }
        else return d;
    };

    dfs(1, 0);
    return kotae;
}

vector<int> generateInput(int N) {
    vector<int> parents(N);
    parents[0] = 0;
    for (int i = 1; i < N; i++) {
        parents[i] = rand() % i;
    }
    return parents;
}