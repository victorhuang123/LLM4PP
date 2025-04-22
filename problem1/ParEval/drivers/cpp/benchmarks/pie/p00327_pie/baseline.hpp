#pragma once

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);i++)

#define REP(i,n) FOR(i,0,n)

#define ALL(v) (v).begin(),(v).end()

#define fi first

#define se second

template<typename A, typename B> inline bool chmax(A &a, B b) { if (a<b) { a=b; return 1; } return 0; }

template<typename A, typename B> inline bool chmin(A &a, B b) { if (a>b) { a=b; return 1; } return 0; }

typedef long long ll;

typedef pair<int, int> pii;

typedef pair<ll, ll> pll;

typedef pair<pll, int> plp;

const ll INF = 1e9+100;

const ll MOD = 1e9+7;

const double EPS = 1e-10;

const bool debug = 0;

//--------------------------------//

bool baseline(int N, const vector<int>& c) {
    bool dp[100][101][10] = {false};

    REP(i, N - 1) if (c[i] == c[i + 1]) dp[i][i + 2][c[i]] = true;

    FOR(s, 2, N + 1) {
        REP(l, N - s + 1) {
            int r = l + s;

            REP(i, 10) REP(j, 10) {
                FOR(k, l + 1, r) {
                    dp[l][r][0] |= dp[l][k][i] & dp[k][r][j]; // xx

                    if (c[l] == c[r - 1]) {
                        dp[l][r][c[l]] |= dp[l + 1][r - 1][i]; // 1x1
                        if (c[l] == c[k]) dp[l][r][c[l]] |= dp[l + 1][k][i] & dp[k + 1][r - 1][j]; // 1x1x1
                    }
                }
            }

            if (l > 0) dp[l - 1][r][c[l - 1]] |= dp[l][r][c[l - 1]];
            if (r < N) dp[l][r + 1][c[r]] |= dp[l][r][c[r]];
        }
    }

    bool ans = false;
    REP(i, 10) ans |= dp[0][N][i];
    return ans;
}

vector<int> generateInput(int N) {
    vector<int> c(N);
    REP(i, N) c[i] = rand() % 10;
    return c;
}