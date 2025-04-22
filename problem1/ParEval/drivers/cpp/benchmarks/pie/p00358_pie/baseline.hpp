#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int h, int n, vector<pair<int, int>>& inputs) {
    vector<vector<int>> dp(h + 1, vector<int>(8, -1));
    vector<int> b(h + 1, 0);
    int ei[4] = {0b100, 0b110, 0b011, 0b001};

    for (int i = 0; i < n; ++i) {
        int x = inputs[i].first;
        int y = inputs[i].second;
        b[y + 1] |= ei[x];
        b[y] |= ei[x];
    }

    function<int(int, int)> dfs = [&](int i, int bit) {
        if (i == h) {
            return 0;
        }
        bit |= b[i];

        if (dp[i][bit] != -1) {
            return dp[i][bit];
        }

        int ret = 0;
        if (bit == 0)
            ret = max(ret, dfs(i + 1, 0b111) + 2);
        if ((bit & (0b100)) == 0)
            ret = max(ret, dfs(i + 1, 0b110) + 1);
        if ((bit & (0b010)) == 0)
            ret = max(ret, dfs(i + 1, 0b111) + 1);
        if ((bit & (0b001)) == 0)
            ret = max(ret, dfs(i + 1, 0b011) + 1);
        ret = max(ret, dfs(i + 1, 0));

        return dp[i][bit] = ret;
    };

    return dfs(1, 0);
}

vector<pair<int, int>> generateInput(int h, int n) {
    vector<pair<int, int>> inputs(n);
    for (int i = 0; i < n; ++i) {
        inputs[i] = {rand() % 4, rand() % h};
    }
    return inputs;
}