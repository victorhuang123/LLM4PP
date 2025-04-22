#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(const vector<vector<int>>& ac) {
    int it = ac.size();
    vector<vector<int>> dp(3, vector<int>(it, -1));

    function<int(int, int)> va = [&](int a, int i) {
        if (i == it) {
            return 0;
        }
        if (dp[a][i] != -1) {
            return dp[a][i];
        }
        int& ans = dp[a][i];
        if (a == 0) {
            ans = max(ans, va(1, i+1) + ac[i][0]);
            ans = max(ans, va(2, i+1) + ac[i][0]);
        }
        if (a == 1) {
            ans = max(ans, va(0, i+1) + ac[i][1]);
            ans = max(ans, va(2, i+1) + ac[i][1]);
        }
        if (a == 2) {
            ans = max(ans, va(0, i+1) + ac[i][2]);
            ans = max(ans, va(1, i+1) + ac[i][2]);
        }
        return ans;
    };

    return max(va(0, 0), max(va(1, 0), va(2, 0)));
}

vector<vector<int>> generateInput(int it) {
    vector<vector<int>> ac(it, vector<int>(3));
    for (int i = 0; i < it; i++) {
        ac[i][0] = rand() % 1000;
        ac[i][1] = rand() % 1000;
        ac[i][2] = rand() % 1000;
    }
    return ac;
}