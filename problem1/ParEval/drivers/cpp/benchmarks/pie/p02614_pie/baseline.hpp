#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int n, int m, int k, vector<vector<char>>& v) {
    int total = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(v[i][j] == '#') total++;
        }
    }

    function<int(int, int)> process = [&](int row, int col) {
        int ret = total;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(v[i][j] == '.') continue;
                bool f = false, g = false;
                if(row >> i & 1) f = true;
                if(col >> j & 1) g = true;

                ret -= (f || g);
            }
        }
        return ret;
    };

    int ans = 0;

    for(int i = 0; i < (1<<n); i++) {
        for(int j = 0; j < (1<<m); j++) {
            if(process(i, j) == k) ans++;
        }
    }

    return ans;
}

vector<vector<char>> generateInput(int n, int m) {
    vector<vector<char>> v(n, vector<char>(m, '#'));
    return v;
}