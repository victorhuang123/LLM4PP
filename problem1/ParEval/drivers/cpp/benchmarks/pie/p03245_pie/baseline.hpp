#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<pair<long long, long long>> generateInput(int n) {
    vector<pair<long long, long long>> input(n);
    for (int i = 0; i < n; i++) {
        input[i] = {rand() % 1000000, rand() % 1000000};
    }
    return input;
}

vector<vector<long long>> baseline(const vector<pair<long long, long long>>& points) {
    int n = points.size();
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) {
        x[i] = points[i].first;
        y[i] = points[i].second;
    }

    int m2 = 0;
    if ((x[0] + y[0]) % 2 == 0) {
        m2 = 1;
        for (int i = 0; i < n; i++)
            x[i]--;
    }
    for (int i = 0; i < n; i++) {
        if ((x[i] + y[i]) % 2 == 0) {
            return {{-1}};
        }
    }
    vector<long long> v;
    for (int i = 0; i <= 31; i++)
        v.push_back(1ll << i);
    if (m2)
        v.push_back(1);
    reverse(v.begin(), v.end());

    vector<vector<long long>> result;
    result.push_back(v);
    for (int i = 0; i < n; i++) {
        string s;
        if (m2)
            s += "R";
        for (int j = 31; j >= 0; j--) {
            int tmp = -1;
            long long now = LLONG_MAX;
            for (int k = 0; k < 4; k++) {
                long long cur = abs(x[i] - dx[k] * (1ll << j)) + abs(y[i] - dy[k] * (1ll << j));
                if (cur < now) {
                    now = cur;
                    tmp = k;
                }
            }
            x[i] -= dx[tmp] * (1ll << j);
            y[i] -= dy[tmp] * (1ll << j);
            s += ch[tmp];
        }
        vector<long long> path;
        for (char c : s) {
            path.push_back(c);
        }
        result.push_back(path);
    }
    return result;
}