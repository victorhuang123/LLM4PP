#pragma once

#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

typedef long long LL;

int baseline(int n, int m, const vector<int>& a, const vector<vector<int>>& c) {
    vector<int> b(m + 1, 0);
    vector<int> dp(1 << n, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= m; i++) {
        for (int u : c[i - 1]) {
            b[i] |= (1 << (u - 1));
        }
    }

    for (int i = 1; i <= m; i++) {
        int u = b[i];
        for (int j = 0; j < (1 << n); j++) {
            if (dp[j] != INT_MAX) {
                if (dp[u | j] != INT_MAX) {
                    dp[u | j] = min(dp[u | j], dp[j] + a[i - 1]);
                } else {
                    dp[u | j] = dp[j] + a[i - 1];
                }
            }
        }
    }

    return (dp[(1 << n) - 1] != INT_MAX) ? dp[(1 << n) - 1] : -1;
}

vector<int> generateInputA(int m) {
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        a[i] = rand() % 100 + 1;
    }
    return a;
}

vector<vector<int>> generateInputC(int m, int n) {
    vector<vector<int>> c(m);
    for (int i = 0; i < m; i++) {
        int cnt = rand() % n + 1;
        for (int j = 0; j < cnt; j++) {
            c[i].push_back(rand() % n + 1);
        }
    }
    return c;
}