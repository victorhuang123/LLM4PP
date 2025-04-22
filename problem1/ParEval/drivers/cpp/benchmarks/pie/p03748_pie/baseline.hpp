#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int n, int m) {
    vector<vector<vector<int>>> f(m + 2, vector<vector<int>>(n + 2, vector<int>(2, 0)));
    int ms = 1e9 + 7;

    f[0][0][1] = 1;

    for (int i = 1; i <= n; i++)
        f[0][i][0] = 1;

    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= 1; k++) {
                if (j) (f[i + 1][j - 1][!(j - 1) | k] += f[i][j][k]) %= ms;
                if (n - j) (f[i + 1][j + 1][k] += f[i][j][k]) %= ms;
                if (j) (f[i + 1][j][k | (j == 1)] += f[i][j][k]) %= ms;
                if (n - j) (f[i + 1][j][k] += f[i][j][k]) %= ms;
            }

    int ans = 0;
    for (int i = 0; i <= n; i++)
        (ans += f[m][i][1]) %= ms;

    return ans;
}

vector<int> generateInput() {
    return {3000, 3000};
}