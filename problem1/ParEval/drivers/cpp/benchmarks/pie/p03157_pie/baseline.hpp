#pragma once

#include<bits/stdc++.h>

using namespace std;

#define IO ios_base::sync_with_stdio(false)

vector<vector<char>> generateInput(int n, int m) {
    vector<vector<char>> s(n + 2, vector<char>(m + 2, '*'));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            s[i][j] = (rand() % 2) ? '#' : '.';
        }
    }
    return s;
}

long long baseline(int n, int m, vector<vector<char>>& s) {
    vector<vector<int>> vs(n + 2, vector<int>(m + 2, 0));
    vector<vector<int>> to(n + 2, vector<int>(m + 2, 0));
    vector<vector<int>> white(n + 2, vector<int>(m + 2, 0));
    long long l = 0;

    auto f = [&](int n, int m, int co, auto&& f) -> void {
        vs[n][m] = 1;
        for (int i = -1; i <= 1; i++) {
            for (int k = -1; k <= 1; k++) {
                char ch = s[n + i][m + k];
                if (abs(i + k) == 1 && ch != '*') {
                    if (vs[n + i][m + k] == 0 && ((co == 1 && ch == '.') || (co == 0 && ch == '#'))) {
                        f(n + i, m + k, 1 - co, f);
                        to[n][m] += to[n + i][m + k];
                        white[n][m] += white[n + i][m + k];
                    }
                }
            }
        }
        to[n][m]++;
        if (s[n][m] == '.') white[n][m]++;
    };

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (vs[i][j] == 0 && s[i][j] == '#') {
                f(i, j, 1, f);
                l += (to[i][j] - white[i][j]) * white[i][j];
            }
        }
    }

    return l;
}