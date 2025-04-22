#pragma once

#include<vector>
#include<algorithm>
#include<utility>

using namespace std;

vector<int> baseline(int n, vector<int>& ids, vector<vector<vector<int>>>& times) {
    vector<pair<int, int>> T(n);

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < 4; j++) {
            int m = times[i][j][0];
            int s = times[i][j][1];
            sum += m * 60 + s;
        }
        T[i] = make_pair(sum, ids[i]);
    }

    sort(T.begin(), T.end());

    vector<int> result;
    result.push_back(T[0].second);
    result.push_back(T[1].second);
    result.push_back(T[n-2].second);

    return result;
}

vector<vector<vector<int>>> generateExampleInput(int n) {
    vector<vector<vector<int>>> times(n, vector<vector<int>>(4, vector<int>(2)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            times[i][j][0] = 1 + (i + j) % 10;
            times[i][j][1] = 30 + (i + j) % 30;
        }
    }
    return times;
}