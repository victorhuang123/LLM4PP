#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int n, vector<pair<int, int>> ranges) {
    int ans = 0;
    int c[1000001] = {0};

    for(int i = 0; i < n; i++) {
        int a = ranges[i].first;
        int b = ranges[i].second;
        for(int j = a; j <= b; j++) {
            c[j] = 1;
        }
    }

    for(int i = 0; i < 1000001; i++) {
        if(c[i] == 1) {
            ans++;
        }
    }

    return ans;
}

vector<pair<int, int>> generateExampleInput() {
    vector<pair<int, int>> ranges;
    for(int i = 0; i < 100000; i++) {
        ranges.push_back({i * 1000 + 1, (i + 1) * 1000});
    }
    return ranges;
}