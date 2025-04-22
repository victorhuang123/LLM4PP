#pragma once

#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int baseline(int n, int m, const vector<int>& op, const vector<int>& x, const vector<int>& y) {
    vector<vector<int>> f(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> g(n + 1, vector<int>(n + 1, 0));
    vector<bool> vis(n + 1, false);

    auto dfs = [&](int u, auto&& dfs) -> void {
        vis[u] = true;
        for (int i = 1; i <= n; ++i) {
            if (g[u][i]) {
                if (!vis[i]) dfs(i, dfs);
                for (int k = 1; k <= n; ++k) {
                    if (f[i][k]) {
                        f[u][k] = f[k][u] = 1;
                    }
                }
            }
        }
    };

    auto check = [&](int mid) -> bool {
        for (int i = 1; i <= n; ++i) {
            fill(f[i].begin(), f[i].end(), 0);
            fill(g[i].begin(), g[i].end(), 0);
            g[i][i] = 1;
        }

        for (int Q = 1; Q <= mid; ++Q) {
            int i = x[Q], j = y[Q], ope = op[Q];
            if (ope == 1) g[i][j] = 1;
            else if (ope == 2) g[i][j] = g[j][i] = 1;
            else if (ope == 4) f[i][j] = f[j][i] = 1;
        }

        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (g[i][k] && g[k][j]) g[i][j] = 1;
                }
            }
        }

        fill(vis.begin(), vis.end(), false);
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) dfs(i, dfs);
        }

        for (int Q = 1; Q <= mid; ++Q) {
            int i = x[Q], j = y[Q], ope = op[Q];
            if (ope == 3) {
                if (f[i][i] && f[j][j]) return false;
                if (g[i][j] && g[j][i]) return false;
            } else if (ope == 5) {
                if (f[i][j] || f[j][i] || f[i][i] || f[j][j]) return false;
            }
        }
        return true;
    };

    int l = 1, r = m, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

vector<int> generateInput(int n, int m) {
    vector<int> op(m + 1), x(m + 1), y(m + 1);
    for (int i = 1; i <= m; ++i) {
        op[i] = rand() % 5 + 1;
        x[i] = rand() % n + 1;
        y[i] = rand() % n + 1;
    }
    return {op, x, y};
}