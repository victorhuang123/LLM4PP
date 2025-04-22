#pragma once

#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int baseline(int n, int m, const vector<pair<int, int>>& data) {
    int ans = 0;
    map<int, int> f;

    for (int i = 0; i <= 10; i++) {
        f[i] += 0;
    }

    for (int i = 0; i < n; i++) {
        int d = data[i].first;
        int p = data[i].second;
        f[p] += d;
    }

    for (int i = 10; i >= 0; i--) {
        while (f[i] && m) {
            m--;
            f[i] -= 1;
        }
        ans += f[i] * i;
    }

    return ans;
}

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> data;
    for (int i = 0; i < n; i++) {
        data.push_back({1, i % 11});
    }
    return data;
}