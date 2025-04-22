#pragma once

#include <vector>
#include <cstring>

using namespace std;

int baseline(int w, int h, const vector<char>& grid) {
    vector<vector<char>> c(w, vector<char>(h, 0));

    for (int i = 0; i < w * h; i++) {
        c[i % w][i / w] = grid[i];
    }

    for (int i = 0; i < w * h; i++) {
        for (int j = 0; j < w * h; j++) {
            if (c[j % w][j / w] == 64) {
                if (j % w > 0 && c[j % w - 1][j / w] == 46) c[j % w - 1][j / w] = 64;
                if (j % w < w - 1 && c[j % w + 1][j / w] == 46) c[j % w + 1][j / w] = 64;
                if (j / w > 0 && c[j % w][j / w - 1] == 46) c[j % w][j / w - 1] = 64;
                if (j / w < h - 1 && c[j % w][j / w + 1] == 46) c[j % w][j / w + 1] = 64;
            }
        }
    }

    int cou = 0;
    for (int i = 0; i < w * h; i++) {
        if (c[i % w][i / w] == 64) cou++;
    }

    return cou;
}

vector<char> generateInput(int w, int h) {
    vector<char> grid(w * h, '.');
    grid[0] = '@';
    return grid;
}