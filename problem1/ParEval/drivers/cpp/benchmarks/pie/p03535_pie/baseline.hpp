#pragma once

#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int dp[100][30][30][30];

int solve(int i, int l, int r, int mn, int N, const vector<int>& D) {
    int &res = dp[i][l][r][mn];
    if (res != -1) {
        return res;
    }
    if (i >= N) {
        return res = mn;
    }
    // left
    res = max(res, solve(i + 1, D[i], r, min({mn, D[i] - l, r - D[i]}), N, D));
    // right
    res = max(res, solve(i + 1, l, 24 - D[i], min({mn, r - (24 - D[i]), (24 - D[i]) - l}), N, D));
    return res;
}

int baseline(int N, const vector<int>& D) {
    vector<int> modifiedD = D;
    for (int i = 0; i < N; i++) {
        modifiedD[i] = min(modifiedD[i], 24 - modifiedD[i]);
    }
    sort(modifiedD.begin(), modifiedD.end());
    memset(dp, -1, sizeof(dp));
    return solve(0, 0, 24, 24, N, modifiedD);
}

vector<int> generateInput(int N) {
    vector<int> D(N);
    for (int i = 0; i < N; i++) {
        D[i] = i % 25; // Ensure values are within 0-24
    }
    return D;
}