#pragma once

#include <vector>

using namespace std;

bool baseline(int n, int m, const vector<vector<char>>& a, const vector<vector<char>>& b) {
    for (int ly = 0; ly < n; ly++) {
        for (int lx = 0; lx < n; lx++) {
            if (ly + m - 1 >= n || lx + m - 1 >= n) continue;

            bool match = true;

            for (int y = 0; y < m; y++) {
                for (int x = 0; x < m; x++) {
                    if (b[y][x] != a[ly + y][lx + x]) {
                        match = false;
                        break;
                    }
                }
                if (!match) break;
            }

            if (match) return true;
        }
    }

    return false;
}

vector<vector<char>> generateInput(int n, int m) {
    vector<vector<char>> a(n, vector<char>(n, 'A'));
    vector<vector<char>> b(m, vector<char>(m, 'A'));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            b[i][j] = 'B';
        }
    }

    return a;
}