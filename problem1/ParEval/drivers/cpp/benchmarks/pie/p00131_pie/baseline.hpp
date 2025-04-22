#pragma once

#include <vector>

using namespace std;

vector<vector<int>> baseline(vector<vector<int>> t) {
    vector<vector<int>> u(10, vector<int>(10)), ans(10, vector<int>(10));
    int flg;

    auto dfs = [&](int x, auto&& dfs) -> void {
        if (x == 10) {
            if (compute(t, u, ans)) {
                flg = 1;
            }
            return;
        }
        ans[0][x] = 0;
        dfs(x + 1, dfs);
        ans[0][x] = 1;
        dfs(x + 1, dfs);
    };

    auto compute = [](vector<vector<int>> t, vector<vector<int>>& u, vector<vector<int>>& ans) -> int {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                u[i][j] = t[i][j];
                if (i) ans[i][j] = 0;
            }
        }

        for (int i = 0; i < 10; i++) {
            if (ans[0][i]) change(0, i, u);
        }

        for (int i = 1; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (u[i - 1][j]) {
                    ans[i][j] = 1;
                    change(i, j, u);
                }
            }
        }

        for (int i = 0; i < 10; i++) {
            if (u[9][i]) return 0;
        }
        return 1;
    };

    auto change = [](int y, int x, vector<vector<int>>& u) -> void {
        u[y][x] = !u[y][x];
        if (y > 0) u[y - 1][x] = !u[y - 1][x];
        if (x > 0) u[y][x - 1] = !u[y][x - 1];
        if (y < 9) u[y + 1][x] = !u[y + 1][x];
        if (x < 9) u[y][x + 1] = !u[y][x + 1];
    };

    flg = 0;
    dfs(0, dfs);
    return ans;
}

vector<vector<int>> generateInput() {
    return vector<vector<int>>(10, vector<int>(10, 1));
}