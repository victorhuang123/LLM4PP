#pragma once

#include <cmath>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

int baseline(int n, int m, const vector<vector<pair<int, int>>>& v) {
    vector<vector<vector<int>>> d(n);
    for (int i = 0; i < n; i++) d[i] = vector<vector<int>>(v[i].size(), vector<int>(m + 1, 999999999));

    priority_queue<tuple<int, int, int, int>> que; // (dist, y, x, z)
    for (int i = 0; i <= 1 && i <= m; i++) {
        for (int j = 0; j < v[i].size(); j++) {
            d[i][j][i] = 0;
            que.push(make_tuple(0, i, j, i));
        }
    }

    while (!que.empty()) {
        tuple<int, int, int, int> t1 = que.top(); que.pop();
        int a1 = -get<0>(t1), b1 = get<1>(t1), c1 = get<2>(t1), d1 = get<3>(t1);
        for (int i = 1; i <= 2 && b1 + i < n; i++) {
            if (i == 2 && d1 == m) continue;
            for (int j = 0; j < v[b1 + i].size(); j++) {
                int s = abs(v[b1][c1].first - v[b1 + i][j].first) * (v[b1][c1].second + v[b1 + i][j].second);
                if (d[b1 + i][j][d1 + i - 1] > a1 + s) {
                    d[b1 + i][j][d1 + i - 1] = a1 + s;
                    que.push(make_tuple(-d[b1 + i][j][d1 + i - 1], b1 + i, j, d1 + i - 1));
                }
            }
        }
    }

    int ret = 999999999;
    for (int i = 0; i <= 1 && i <= m; i++) {
        for (int j = 0; j < v[n - i - 1].size(); j++) {
            for (int k = 0; k <= m - i; k++) {
                ret = min(ret, d[n - i - 1][j][k]);
            }
        }
    }

    return ret;
}

vector<vector<pair<int, int>>> generateInput(int n, int m) {
    vector<vector<pair<int, int>>> v(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            v[i].push_back(make_pair(rand() % 100, rand() % 100));
        }
    }
    return v;
}