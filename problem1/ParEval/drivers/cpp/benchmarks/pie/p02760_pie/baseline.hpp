#pragma once

#include <vector>
#include <map>
#include <utility>

using namespace std;

vector<int> generateInput() {
    vector<int> inputs(1000000, 1); // Large input to test efficiency
    return inputs;
}

bool baseline(const vector<vector<int>>& a, const vector<int>& inputs) {
    vector<vector<int>> vis(4, vector<int>(4, 0));
    map<int, pair<int, int>> mp;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            mp[a[i][j]] = {i, j};
        }
    }
    for (int k : inputs) {
        if (mp.find(k) != mp.end()) {
            pair<int, int> tmp = mp[k];
            if (tmp.first <= 3 && tmp.second <= 3 && tmp.first > 0 && tmp.second > 0) {
                vis[tmp.first][tmp.second] = 1;
            }
        }
    }
    for (int i = 1; i <= 3; ++i) {
        int ans = 0;
        for (int j = 1; j <= 3; ++j) {
            if (vis[i][j] == 1) {
                ans++;
            }
        }
        if (ans == 3) {
            return true;
        }
    }
    if (vis[1][1] && vis[2][2] && vis[3][3] || vis[1][3] && vis[2][2] && vis[3][1]) {
        return true;
    }
    for (int i = 1; i <= 3; ++i) {
        int ans = 0;
        for (int j = 1; j <= 3; ++j) {
            if (vis[j][i] == 1) {
                ans++;
            }
        }
        if (ans == 3) {
            return true;
        }
    }
    return false;
}