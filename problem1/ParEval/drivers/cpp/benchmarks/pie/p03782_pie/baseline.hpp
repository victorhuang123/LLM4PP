#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<int,int> pii;

typedef pair<long long,long long> pll;

#define ep emplace_back

#define pb push_back

#define mp make_pair

#define rep(i,n) for(int i=0;i<(n);++i)

constexpr int mod=1000000007;

constexpr int mod1=998244353;

vector<int> dx={0,1,0,-1},dy={-1,0,1,0};

bool inside(int y,int x,int h,int w){

	if(y<h && y>=0 && x<w && x>=0) return true;

	return false;

}

int baseline(int n, int k, vector<int>& a) {
    sort(a.begin(), a.end());
    vector<vector<int>> dp(n + 2, vector<int>(5010));
    dp[0][0] = 1;
    int ng = 0, ok = n + 1;

    while (ok - ng > 1) {
        int mid = (ok + ng) / 2;
        if (a.at(mid - 1) >= k) {
            ok = mid;
            continue;
        }

        rep(i, n + 1) {
            rep(j, k + 1) {
                dp[i][j] = 0;
            }
        }
        dp[0][0] = 1;

        rep(i, n) {
            rep(j, k + 1) {
                if (i + 1 != mid && j - a.at(i) >= 0) dp[i + 1][j] |= dp[i][j - a.at(i)];
                dp[i + 1][j] |= dp[i][j];
            }
        }

        bool flg = false;
        for (int i = k - a.at(mid - 1); i < k; i++) {
            if (dp[n][i]) {
                flg = true;
                break;
            }
        }

        if (flg) ok = mid;
        else ng = mid;
    }

    return ng;
}

vector<int> generateInput(int n, int k) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % k + 1;
    }
    return a;
}