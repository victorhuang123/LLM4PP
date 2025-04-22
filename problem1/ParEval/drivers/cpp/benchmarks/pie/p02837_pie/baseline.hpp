#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int N, vector<vector<pair<int, int>>>& P) {
    int ans = 0;
    for (int tmp = 0; tmp < (1 << N); tmp++) {
        bitset<15> s(tmp);
        bool consistent = true;
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            if (s.test(i)) {
                cnt++;
                for (auto p : P[i]) {
                    if (p.second == 1 && !s.test(p.first)) {
                        consistent = false;
                    }
                    if (p.second == 0 && s.test(p.first)) {
                        consistent = false;
                    }
                }
            }
        }
        if (consistent) {
            ans = max(ans, cnt);
        }
    }
    return ans;
}

vector<vector<pair<int, int>>> generateInput(int N) {
    return vector<vector<pair<int, int>>>(N, vector<pair<int, int>>(N, {0, 1}));
}