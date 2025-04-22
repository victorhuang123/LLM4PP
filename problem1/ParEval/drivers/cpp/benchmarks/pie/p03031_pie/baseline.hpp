#pragma once

#include <bits/stdc++.h>
using namespace std;

int baseline(int n, int m, vector<vector<int>>& vec, vector<int>& q) {
    int ans = 0;
    for (int i = 0; i < (1 << n); i++) {
        bitset<30> bits(i);
        bool ok = true;
        for (int j = 0; j < m; j++) {
            int g = 0;
            for (int k = 0; k < vec[j].size(); k++) {
                if (bits[vec[j][k]]) {
                    g++;
                }
            }
            if ((g & 1) != q[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans++;
        }
    }
    return ans;
}

vector<vector<int>> generateInput(int n, int m) {
    vector<vector<int>> vec(m);
    for (int i = 0; i < m; i++) {
        int size = rand() % n + 1;
        for (int j = 0; j < size; j++) {
            vec[i].push_back(rand() % n);
        }
    }
    return vec;
}

vector<int> generateQuery(int m) {
    vector<int> q(m);
    for (int i = 0; i < m; i++) {
        q[i] = rand() % 2;
    }
    return q;
}