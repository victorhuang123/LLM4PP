#pragma once

#include<bits/stdc++.h>

using namespace std;

#define MAX 100005
#define INF (1e9+1)

int baseline(int n, int W, vector<pair<int, int>>& items) {
    int dp[MAX];
    fill(dp, dp + MAX, INF);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        int v = items[i].first;
        int w = items[i].second;
        for (int j = MAX - 1; j >= v; j--) {
            dp[j] = min(dp[j], dp[j - v] + w);
        }
    }

    for (int i = MAX - 1; i >= 0; i--) {
        if (dp[i] <= W) {
            return i;
        }
    }
    return 0;
}

vector<pair<int, int>> generateInput(int n, int W) {
    vector<pair<int, int>> items(n, {100, 100});
    return items;
}