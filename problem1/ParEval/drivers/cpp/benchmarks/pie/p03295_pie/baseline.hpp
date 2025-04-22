#pragma once

#include <bits/stdc++.h>
using namespace std;

int baseline(int n, int m, vector<pair<int, int>>& v) {
    auto cmp = [](pair<int,int> A, pair<int,int> B) {
        if (A.second == B.second)
            return A.first < B.first;
        return A.second < B.second;
    };
    sort(v.begin(), v.end(), cmp);
    int ans = 1;
    int cur = v[0].second;
    for (int i = 1; i < m; i++) {
        if (v[i].first >= cur) {
            ans++;
            cur = v[i].second;
        }
    }
    return ans;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> v(m);
    for (int i = 0; i < m; i++) {
        v[i].first = rand() % n;
        v[i].second = v[i].first + rand() % (n - v[i].first);
    }
    return v;
}