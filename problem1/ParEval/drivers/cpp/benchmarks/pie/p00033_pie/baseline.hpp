#pragma once

#include<bits/stdc++.h>

using namespace std;

bool check(int x, const vector<int>& a) {
    int pre = 0;
    for (int i = 0; i < 10; i++) if (x & (1 << i)) {
        if (a[i] < pre) return false;
        pre = a[i];
    }
    return true;
}

bool dfs(int i, int x, int pre, const vector<int>& a) {
    if (i == 10) {
        return check(x, a);
    }
    bool temp = false;
    if (a[i] > pre) temp = dfs(i + 1, x, a[i], a);
    return temp || dfs(i + 1, x | (1 << i), pre, a);
}

vector<bool> baseline(int T, const vector<vector<int>>& a) {
    vector<bool> result(T);
    for (int t = 0; t < T; t++) {
        result[t] = dfs(1, 0, a[t][0], a[t]);
    }
    return result;
}

vector<vector<int>> generateInput(int T) {
    vector<vector<int>> a(T, vector<int>(10));
    for (int t = 0; t < T; t++) {
        for (int i = 0; i < 10; i++) {
            a[t][i] = rand() % 1000;
        }
    }
    return a;
}