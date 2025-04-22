#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int n, int m, vector<vector<char>>& grid) {
    vector<vector<int>> ln(n), vln(m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') {
                ln[i].push_back(j);
                vln[j].push_back(i);
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') {
                continue;
            }

            int pos1 = upper_bound(ln[i].begin(), ln[i].end(), j) - ln[i].begin();
            int pos2 = upper_bound(vln[j].begin(), vln[j].end(), i) - vln[j].begin();
            int posa = pos1 - 1;
            int posb = pos2 - 1;

            if (pos1 == ln[i].size()) {
                pos1 = m - 1;
            } else {
                pos1 = ln[i][pos1] - 1;
            }

            if (pos2 == vln[j].size()) {
                pos2 = n - 1;
            } else {
                pos2 = vln[j][pos2] - 1;
            }

            if (posa == -1) {
                posa = 0;
            } else {
                posa = ln[i][posa] + 1;
            }

            if (posb == -1) {
                posb = 0;
            } else {
                posb = vln[j][posb] + 1;
            }

            int num = pos1 - posa + pos2 - posb + 1;
            ans = max(ans, num);
        }
    }

    return ans;
}

vector<vector<char>> generateInput(int n, int m) {
    vector<vector<char>> grid(n, vector<char>(m, '.'));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (rand() % 2 == 0) {
                grid[i][j] = '#';
            }
        }
    }
    return grid;
}