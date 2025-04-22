#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> baseline(int r, int c, int a, int b) {
    vector<vector<int>> mp(r + 1, vector<int>(c + 1, 0));

    for(int i = 1; i <= r; i++) {
        if(i & 1) {
            for(int j = 1; j <= a; j++) {
                mp[i][j] = 1;
            }
        } else {
            for(int j = a + 1; j <= c; j++) {
                mp[i][j] = 1;
            }
        }
    }

    if(b < r / 2) {
        for(int i = 1; i <= r / 2 - b; i++) {
            for(int j = 1; j <= a; j++) {
                mp[i * 2][j] = 1;
            }
            for(int j = a + 1; j <= c; j++) {
                mp[i * 2][j] = 0;
            }
        }
    }

    return mp;
}

vector<vector<int>> generateInput() {
    int r = 1000, c = 1000, a = 500, b = 250;
    return baseline(r, c, a, b);
}