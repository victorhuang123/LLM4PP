#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

typedef long double llf;

typedef pair<lint, lint> pi;

const int MAXN = 2005, N = MAXN;

const int mod = 1e9 + 7, inv2 = (mod + 1) / 2;

int dp[MAXN][3][MAXN], odp[3][MAXN], sz[MAXN];

vector<int> adj[N];

void sadd(int &x, int y) {

	x += y;

	while (x >= mod) x -= mod;

}

void dfs(int v, int p = -1) {

	dp[v][0][1] = 1;

	sz[v] = 1;

	for (int u : adj[v]) {

		if (u != p) {

			dfs(u, v);

			memcpy(odp, dp[v], sizeof dp[v]);

			memset(dp[v], 0, sizeof dp[v]);

			for (int dv = 0; dv <= 2; ++dv) {

				for (int du = 0; du <= 2; ++du) {

					for (int use = 0; use <= 1; ++use) {

						if (use == 1 && (du > 1 || dv > 1)) continue;

						for (int cv = 1; cv <= sz[v]; ++cv)

							for (int cu = 1; cu <= sz[u]; ++cu) {

								int ways = (use == 1 ? mod - 1 : 1);

								if (use) {

									if (du == 0 && dv == 0) 

										ways = (long long) ways * 2 % mod;

									if (du == 1 && dv == 1)

										ways = (long long) ways * inv2 % mod;

								}

								sadd(dp[v][dv + use][cv + cu - use], 

										odp[dv][cv] * (long long) dp[u][du][cu] % mod * ways % mod);

							}

					}

				}

			}

			sz[v] += sz[u];

		}

	}

}

int baseline(int n, const vector<int>& parents) {

    for (int j = 1; j < n; ++j) {

        int p = parents[j - 1];

        adj[--p].push_back(j);

    }

    dfs(0);

    int f[N];

    f[0] = 1;

    for (int j = 1; j < N; ++j) f[j] = (long long) f[j - 1] * j % mod;

    int res = 0;

    for (int j = 0; j < N; ++j)

        for (int d = 0; d <= 2; ++d) if (dp[0][d][j]) {

            sadd(res, dp[0][d][j] * (long long) f[j] % mod);

        }

    return res;

}

vector<int> generateInput(int n) {

    vector<int> parents(n - 1);

    for (int i = 0; i < n - 1; ++i) {

        parents[i] = i + 1;

    }

    return parents;

}