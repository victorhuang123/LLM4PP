#pragma once

#include<vector>
#include<utility>

using namespace std;

vector<pair<pair<int, int>, pair<int, int>>> baseline(int h, int w, vector<vector<int>>& a) {
    vector<pair<pair<int, int>, pair<int, int>>> operations;

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w - 1; j++) {
            if(a[i][j] % 2 == 1) {
                a[i][j] -= 1;
                a[i][j + 1] += 1;
                operations.push_back(make_pair(make_pair(i, j), make_pair(i, j + 1)));
            }
        }
        if(i != h - 1 && a[i][w - 1] % 2 == 1) {
            a[i][w - 1] -= 1;
            a[i + 1][w - 1] += 1;
            operations.push_back(make_pair(make_pair(i, w - 1), make_pair(i + 1, w - 1)));
        }
    }

    return operations;
}

vector<vector<int>> generateInput(int h, int w) {
    vector<vector<int>> a(h, vector<int>(w, 1));
    return a;
}