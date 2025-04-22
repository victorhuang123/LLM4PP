#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cfloat>

using namespace std;

vector<string> baseline(int n, vector<vector<char>> f, vector<int> w, vector<int> s) {
    vector<int> a(n), b(n);
    vector<bool> u(n, false);
    double maxg = -DBL_MAX;

    auto dfs = [&](int x, int tw, int m, double g, auto&& dfs) -> void {
        if (m == n) {
            if (maxg < g) {
                maxg = g;
                for (int i = 0; i < n; i++) {
                    b[i] = a[i];
                }
            }
            return;
        }
        if (x >= n) {
            return;
        }
        if (!u[x] && tw <= s[x]) {
            u[x] = true;
            tw += w[x];
            a[m] = x;
            dfs(0, tw, m + 1, g + w[x] * (m + 1), dfs);
            tw -= w[x];
            u[x] = false;
        }
        dfs(x + 1, tw, m, g, dfs);
    };

    dfs(0, 0, 0, 0., dfs);

    vector<string> result(n);
    for (int i = n - 1; i >= 0; i--) {
        result[n - 1 - i] = string(f[b[i]].begin(), f[b[i]].end());
    }

    return result;
}

vector<vector<char>> generateInput(int n) {
    vector<vector<char>> f(n, vector<char>(21, 'a'));
    vector<int> w(n, 1);
    vector<int> s(n, n);
    return f;
}