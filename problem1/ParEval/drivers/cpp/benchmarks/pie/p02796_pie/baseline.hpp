#pragma once

#include<bits/stdc++.h>
using namespace std;

int baseline(int N, vector<pair<int, int>>& XL) {
    sort(XL.begin(), XL.end());
    int mae = -2e9;
    int kotae = 0;
    for(int i = 0; i < N; i++) {
        if (mae <= XL[i].second) {
            kotae++;
            mae = XL[i].first;
        }
    }
    return kotae;
}

vector<pair<int, int>> generate_input(int N) {
    vector<pair<int, int>> XL(N);
    for(int i = 0; i < N; i++) {
        int x = rand() % 1000000;
        int l = rand() % 1000000;
        XL[i] = {x + l, x};
    }
    return XL;
}