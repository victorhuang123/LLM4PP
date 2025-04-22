#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll baseline(int n, const vector<int>& a) {
    const int N = 200010;
    vector<vector<ll>> dp(N, vector<ll>(5, -1));
    dp[0][0] = 0;

    for (int i = 1; i <= n + 1; ++i) {
        for (int j = 0; j <= 0; ++j) {
            if (dp[i - 1][j] != -1) {
                if (dp[i][0] == -1 || dp[i][0] > dp[i - 1][j] + a[i]) {
                    dp[i][0] = dp[i - 1][j] + a[i];
                }
            }
        }
        for (int j = 0; j <= 1; ++j) {
            if (dp[i - 1][j] != -1) {
                ll val = dp[i - 1][j] + (a[i] == 0 ? 2 : a[i] & 1);
                if (dp[i][1] == -1 || dp[i][1] > val) {
                    dp[i][1] = val;
                }
            }
        }
        for (int j = 0; j <= 2; ++j) {
            if (dp[i - 1][j] != -1) {
                ll val = dp[i - 1][j] + !(a[i] & 1);
                if (dp[i][2] == -1 || dp[i][2] > val) {
                    dp[i][2] = val;
                }
            }
        }
        for (int j = 0; j <= 3; ++j) {
            if (dp[i - 1][j] != -1) {
                ll val = dp[i - 1][j] + (a[i] == 0 ? 2 : a[i] & 1);
                if (dp[i][3] == -1 || dp[i][3] > val) {
                    dp[i][3] = val;
                }
            }
        }
        for (int j = 0; j <= 4; ++j) {
            if (dp[i - 1][j] != -1) {
                ll val = dp[i - 1][j] + a[i];
                if (dp[i][4] == -1 || dp[i][4] > val) {
                    dp[i][4] = val;
                }
            }
        }
    }

    ll result = LLONG_MAX;
    for (int j = 0; j < 5; ++j) {
        if (dp[n + 1][j] != -1 && dp[n + 1][j] < result) {
            result = dp[n + 1][j];
        }
    }
    return result;
}

vector<int> generateInput(int n) {
    vector<int> a(n + 2);
    for (int i = 1; i <= n; ++i) {
        a[i] = rand() % 100;
    }
    return a;
}