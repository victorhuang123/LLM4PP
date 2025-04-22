#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> baseline(int h, int w, int k, vector<vector<char>>& s) {
    vector<vector<int>> a(h, vector<int>(w, 0));
    int tmp = 0;
    int count = h;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') {
                tmp += 1;
                a[i][j] = tmp;
                count = min(i, count);
            }
        }
    }

    tmp = 0;

    for (int i = 0; i < h; i++) {
        tmp = 0;
        for (int j = 0; j < w; j++) {
            if (a[i][j] == 0) {
                a[i][j] = tmp;
            } else {
                if (tmp == 0) {
                    for (int p = 0; p < j; p++) {
                        a[i][p] = a[i][j];
                    }
                }
                tmp = a[i][j];
            }
        }
    }

    if (a[0][0] == 0) {
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < w; j++) {
                a[i][j] = a[count][j];
            }
        }
    }

    for (int i = 0; i < h; i++) {
        if (a[i][0] == 0) {
            for (int j = 0; j < w; j++) {
                a[i][j] = a[i - 1][j];
            }
        }
    }

    return a;
}

vector<vector<char>> generateInput(int h, int w) {
    vector<vector<char>> s(h, vector<char>(w, '#'));
    return s;
}