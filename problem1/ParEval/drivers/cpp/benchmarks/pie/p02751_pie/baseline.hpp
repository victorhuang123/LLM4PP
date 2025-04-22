#pragma once

#include<bits/stdc++.h>
using namespace std;

void solve(int l, int r, int x, int d, vector<int>& f) {
    if (l == r) {
        f[l] = d;
        return;
    }
    int mid = (l + r) >> 1;
    if (x & 1) {
        solve(l, mid, x - 1, d, f);
        solve(mid + 1, r, x - 1, d | (1 << x), f);
    } else {
        solve(l, mid, x - 1, d | (1 << x), f);
        solve(mid + 1, r, x - 1, d, f);
    }
}

vector<vector<int>> baseline(int n, int m) {
    int h = max(n, m);
    vector<vector<int>> a(1 << h, vector<int>(1 << h, 0));
    vector<vector<int>> w(h, vector<int>(1 << h, 0));
    vector<int> f(1 << h, 0);

    for (int i = 0; i < h; ++i) {
        for (int j = 1; j < (1 << h); ++j) {
            w[h - 1 - i][j] = (j & -j) == (1 << i);
        }
    }

    solve(1, (1 << h) - 1, h - 1, 0, f);

    for (int i = 1; i < (1 << h); ++i) {
        if (f[i] == 0) {
            for (int j = i; j < (1 << h); ++j) {
                f[j] = f[j + 1];
            }
            break;
        }
    }

    for (int i = 1; i < (1 << h); ++i) {
        for (int j = 1; j < (1 << h); ++j) {
            for (int k = 0; k < h; ++k) {
                if ((i & -i) >> k & 1) {
                    a[i][j] |= w[k][j];
                }
            }
        }
    }

    vector<vector<int>> result;
    if (n < m) {
        result.resize(1 << n, vector<int>(1 << m, 0));
        for (int i = 1; i < (1 << n); ++i) {
            for (int j = 1; j < (1 << m); ++j) {
                result[i - 1][j - 1] = a[i][j];
            }
        }
    } else {
        result.resize(1 << n, vector<int>(1 << m, 0));
        for (int i = 1; i < (1 << n); ++i) {
            for (int j = 1; j < (1 << m); ++j) {
                result[i - 1][j - 1] = a[j][i];
            }
        }
    }

    return result;
}

vector<vector<int>> generateInput(int n, int m) {
    return vector<vector<int>>(1 << n, vector<int>(1 << m, 0));
}