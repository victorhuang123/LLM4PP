#pragma once

#include <bits/stdc++.h>

#define INF 1e9

using namespace std;

bool baseline(vector<vector<int>>& A) {
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());

    int n = A.size();
    for (int i = 0; i < n; i++) {
        vector<int> used(10, 0);
        for (int j = 0; j < A[i].size(); j++) {
            if (used[A[i][j]]++) return true;
        }
    }

    vector<vector<int>> dp(1 << 10, vector<int>(1 << 10, INF));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = (1 << 10) - 1; j >= 0; j--) {
            for (int k = (1 << 10) - 1; k >= 0; k--) {
                if (dp[j][k] == INF || dp[j][k] == 10) continue;
                if ((j && k) && __builtin_popcount(j & k) == dp[j][k]) return true;

                for (int l = 0, nj = j; l < (int)A[i].size(); l++) {
                    int num = A[i][l];
                    if (l) dp[nj][k | (1 << num)] = min(dp[nj][k | (1 << num)], dp[j][k] + 1);
                    if (j & (1 << num)) break;
                    nj |= (1 << num);
                    dp[nj][k] = min(dp[nj][k], dp[j][k] + 1);
                }
            }
        }
    }

    for (int i = 1; i < (1 << 10); i++) {
        for (int j = 1; j < (1 << 10); j++) {
            if (__builtin_popcount(i & j) == dp[i][j]) return true;
        }
    }

    return false;
}

vector<vector<int>> generateInput() {
    vector<vector<int>> A(1000, vector<int>(10));
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 10; j++) {
            A[i][j] = rand() % 10;
        }
    }
    return A;
}