#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> generateInput(int N) {
    vector<vector<pair<int, int>>> input(N);
    for(int i = 0; i < N; i++) {
        int M = 16, L = rand() % 100 + 1;
        vector<pair<int, int>> intervals;
        for(int j = 0; j < M; j++) {
            int S = rand() % 16, E = rand() % 16;
            if(S > E) swap(S, E);
            intervals.push_back({S, E});
        }
        input[i] = intervals;
    }
    return input;
}

int baseline(int N, const vector<vector<pair<int, int>>>& input) {
    vector<int> dp(1 << 16, 0);
    for(int i = 0; i < N; i++) {
        int M = input[i].size(), L = rand() % 100 + 1;
        int bitMask = 0;
        for(int j = 0; j < M; j++) {
            int S = input[i][j].first, E = input[i][j].second;
            bitMask |= (1 << E) - (1 << S);
        }
        for(int j = 0; j < 1 << 16; j++) {
            if(!(bitMask & j)) {
                dp[bitMask | j] = max(dp[bitMask | j], dp[j] + L);
            }
        }
    }
    return dp[(1 << 16) - 1];
}