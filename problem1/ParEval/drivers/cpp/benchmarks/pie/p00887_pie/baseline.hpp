#pragma once

#include <bits/stdc++.h>

using namespace std;

int guass(int n, vector<vector<int>>& a) {
    int i, j, p, row = 0, col = 0;

    for (; row < n && col < n; row++, col++) {
        for (i = row, p = row; i < n; i++)
            if (a[i][col]) { p = i; break; }

        if (p != row)
            for (j = col; j <= n; j++)
                swap(a[p][j], a[row][j]);

        if (!a[row][col]) {
            row--;
            continue;
        }

        for (i = row + 1; i < n; i++)
            if (a[i][col])
                for (j = col + 1; j <= n; j++)
                    a[i][j] ^= a[row][j];
    }

    for (i = row; i < n; i++)
        if (a[i][n]) return 0;

    return 1;
}

int baseline(int n, int m, int d, vector<vector<int>>& grid) {
    vector<vector<int>> a(n * m, vector<int>(n * m + 1, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i * m + j][n * m] = grid[i][j];
            a[i * m + j][i * m + j] = 1;
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    if (abs(x - i) + abs(y - j) == d)
                        a[i * m + j][x * m + y] = 1;
                }
            }
        }
    }

    return guass(n * m, a);
}

vector<vector<int>> generateInput(int n, int m) {
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = rand() % 2;
        }
    }
    return grid;
}