#pragma once

#include<bits/stdc++.h>

using namespace std;

#define int unsigned long long

int baseline(int a, int b, vector<vector<int>>& c) {
    int w = b;
    vector<int> e(w + 1, 0);
    int f = 0;

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < c[i].size(); j++) {
            e[c[i][j]]++;
        }
    }

    for (int i = 0; i <= w; i++) {
        if (e[i] == a) f++;
    }

    return f;
}

vector<vector<int>> generateInput(int a, int b) {
    vector<vector<int>> c(a, vector<int>(b));
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            c[i][j] = j + 1;
        }
    }
    return c;
}