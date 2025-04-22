#pragma once

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

vector<int> baseline(int n, vector<pair<int, int>>& p) {
    for(int i = 1; i <= n; i++) {
        p[i].first = i;
        p[i].second = rand() % 1000000; // Random value for testing
    }
    sort(p.begin() + 1, p.begin() + n + 1, [](pair<int,int> a, pair<int,int> b) {
        return a.second < b.second;
    });
    vector<int> result;
    for(int i = 1; i <= n; i++) {
        result.push_back(p[i].first);
    }
    return result;
}