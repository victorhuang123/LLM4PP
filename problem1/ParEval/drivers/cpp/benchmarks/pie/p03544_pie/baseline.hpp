#pragma once

#include <vector>
#include <algorithm>

using namespace std;

vector<int> baseline(int n) {
    vector<vector<int>> s(n + 1, vector<int>(1000, 0));
    s[0][0] = 2;
    s[1][0] = 1;
    int num = 0;

    for (int i = 2; i <= n; i++) {
        for (int k = 0; k <= num; k++) {
            s[i][k] += s[i-1][k] + s[i-2][k];
            if (s[i][k] >= 10) {
                s[i][k+1]++;
                s[i][k] -= 10;
            }
        }
        if (s[i][num+1] != 0) {
            num++;
        }
    }

    vector<int> result;
    for (int i = num; i >= 0; i--) {
        result.push_back(s[n][i]);
    }

    return result;
}

vector<int> generateInput() {
    return {1000};
}