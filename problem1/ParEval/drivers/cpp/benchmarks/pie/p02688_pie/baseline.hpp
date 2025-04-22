#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int n, int k, vector<vector<int>> &groups) {
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < groups[i].size(); j++) {
            int u = groups[i][j];
            cnt[u]++;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 0) ans++;
    }
    return ans;
}

vector<vector<int>> generateInput(int n, int k) {
    vector<vector<int>> groups(k);
    for (int i = 0; i < k; i++) {
        int size = rand() % (n / 2) + 1;
        for (int j = 0; j < size; j++) {
            groups[i].push_back(rand() % n + 1);
        }
    }
    return groups;
}