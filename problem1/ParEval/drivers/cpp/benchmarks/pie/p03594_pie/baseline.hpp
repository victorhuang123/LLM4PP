#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> baseline(int a, int b, int c) {
    string mon = "RYGB";
    vector<vector<char>> result(a, vector<char>(b));
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            int m = ((i + j) % (c * 2) + (c * 2)) % (c * 2) / c;
            int n = ((i - j) % (c * 2) + (c * 2)) % (c * 2) / c;
            result[i][j] = mon[m * 2 + n];
        }
    }
    return result;
}

vector<vector<char>> generateInput() {
    int a = 1000, b = 1000, c = 500;
    return baseline(a, b, c);
}