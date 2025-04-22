#pragma once

#include <bits/stdc++.h>

using namespace std;

long long baseline(int n, int A, vector<int>& a) {
    long long f[2][51][2510] = {0};
    f[0][0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        memset(f[i & 1], 0, sizeof(f[i & 1]));

        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= 2500; ++k) {
                f[i & 1][j][k] = ((k - a[i] >= 0 && j > 0) ? f[i & 1 ^ 1][j - 1][k - a[i]] : 0) + f[(i & 1) ^ 1][j][k];
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += f[n & 1][i][i * A];
    }

    return ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    return a;
}