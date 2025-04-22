#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int n, vector<pair<int, int>>& intervals) {
    vector<int> h(100002, 0);

    for (int i = 0; i < n; i++) {
        int a = intervals[i].first;
        int b = intervals[i].second;
        h[a]++;
        if (b + 1 < 100002) h[b+1]--;
    }

    int ma = 0;
    for (int i = 1; i < 100002; i++) {
        h[i] += h[i - 1];
        ma = max(ma, h[i]);
    }

    return ma;
}

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> intervals;
    for (int i = 1; i <= n; i++) {
        intervals.push_back({i, n - i + 1});
    }
    return intervals;
}