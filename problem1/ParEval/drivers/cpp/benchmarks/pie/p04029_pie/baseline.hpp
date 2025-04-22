#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> generateInput(int n) {
    vector<vector<int>> vi(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            vi[i].push_back(j);
            vi[j].push_back(i);
        }
    }
    return vi;
}

int baseline(int n, vector<vector<int>>& vi) {
    vector<int> arr2(n, -1);
    vector<bool> check(n, false);

    function<bool(int, int)> dfs = [&](int node, int c) -> bool {
        check[node] = true;
        arr2[node] = c;
        for (int child : vi[node]) {
            if (!check[child]) {
                if (!dfs(child, c ^ 1)) {
                    return false;
                }
            } else if (arr2[node] == arr2[child]) {
                return false;
            }
        }
        return true;
    };

    for (int i = 0; i < n; ++i) {
        if (!check[i]) {
            if (!dfs(i, 0)) {
                return -1;
            }
        }
    }
    return n * (n + 1) / 2;
}