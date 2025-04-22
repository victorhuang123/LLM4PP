#pragma once

#include <bits/stdc++.h>

#define N 510

#define int long long

using namespace std;

vector<vector<int>> generateInput(int n) {
    vector<vector<int>> a(N, vector<int>(N, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j) {
                a[i][j] = rand() % 1000000 + 1;
            }
        }
    }
    return a;
}

int baseline(int n, const vector<vector<int>>& a) {
    vector<vector<int>> b(N, vector<int>(N, 0));
    vector<vector<int>> c(N, vector<int>(N, 0));
    vector<vector<int>> f(N, vector<int>(N, 0x7f7f7f7f));

    for (int i = 1; i <= n; ++i) {
        for (int j = n; j >= i + 1; --j) {
            b[i][j] = b[i][j + 1];
            for (int k = 1; k <= i; ++k) {
                b[i][j] += a[j][k];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n + 1; ++j) {
            c[i][j] = c[i][j - 1];
            for (int k = i; k <= j - 1; ++k) {
                c[i][j] += a[k][j];
            }
        }
    }

    f[0][0] = 0;

    for (int i = 0; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            if (f[i][j] < 1e18) {
                for (int k = j + 1; k <= n + 1; ++k) {
                    f[j][k] = min(f[j][k], f[i][j] + c[j + 1][k] + b[j][k + 1] - b[i][k + 1]);
                }
            }
        }
    }

    int minn = 1e18;
    for (int i = 0; i <= n; ++i) {
        minn = min(minn, f[i][n + 1]);
    }

    return minn;
}