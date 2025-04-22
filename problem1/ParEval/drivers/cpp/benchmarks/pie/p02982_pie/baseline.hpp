#pragma once

#include <vector>
#include <cmath>

using namespace std;

int baseline(int n, int d, vector<vector<int>>& v) {
    int cnt = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = 0;
            for (int k = 0; k < d; ++k) {
                sum += (v[i][k] - v[j][k]) * (v[i][k] - v[j][k]);
            }
            int dist = sqrt(sum);
            if (dist * dist == sum) {
                cnt++;
            }
        }
    }
    return cnt;
}

vector<vector<int>> generateInput(int n, int d) {
    vector<vector<int>> v(n, vector<int>(d, 1));
    return v;
}