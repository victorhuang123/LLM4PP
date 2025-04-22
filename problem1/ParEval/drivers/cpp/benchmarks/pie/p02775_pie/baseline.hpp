#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(const string& input) {
    int n = input.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, -1));
    vector<int> x(n + 1);
    for (int i = 1; i <= n; ++i) x[i] = input[i - 1] - '0';

    function<int(int, bool)> f = [&](int pos, bool st) -> int {
        if (pos > n) return 0;
        if (dp[pos][st] != -1) return dp[pos][st];

        if (st) return dp[pos][st] = min(f(pos + 1, 0) + x[pos], f(pos + 1, 1) + 9 - x[pos]);
        return dp[pos][st] = min(f(pos + 1, 0) + x[pos], f(pos + 1, 1) + 11 - x[pos]);
    };

    return f(1, 0);
}

string generateInput() {
    return string(1000000, '9');
}