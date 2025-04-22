#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

int memo[100001];

vector<int> V[100001];

int dfs(int A) {

	if (memo[A] != -1) return memo[A];

	int saidai = 0;

	for (int i : V[A]) {

		saidai = max(saidai, dfs(i));

	}

	memo[A] = saidai + 1;

	return memo[A];

}

int baseline(int N, int M, vector<pair<int, int>>& edges) {

	rep(i, M) {

		int x = edges[i].first;

		int y = edges[i].second;

		V[x].pb(y);

	}

	rep1(i, N) memo[i] = -1;

	int saidai = 0;

	rep1(i, N) {

		saidai = max(saidai, dfs(i) - 1);

	}

	return saidai;

}

vector<pair<int, int>> generateInput(int N, int M) {

    vector<pair<int, int>> edges;

    for (int i = 1; i <= M; i++) {

        int x = rand() % N + 1;

        int y = rand() % N + 1;

        edges.pb(mp(x, y));

    }

    return edges;

}