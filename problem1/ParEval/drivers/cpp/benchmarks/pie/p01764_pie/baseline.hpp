#pragma once

#include<vector>
#include<algorithm>

using namespace std;

#define INF (1<<24)

int calc(int X, int Y) {
    int res = 0, c = -1, a, b;
    for (int I = 0; I < 50; I++) {
        if (c == -1 || c + a + b < 10) c = 0;
        else c = 1;
        a = X % 10;
        b = Y % 10;
        X /= 10;
        Y /= 10;
        res += (a * b + c);
    }
    return res;
}

int solve(int l, int r, vector<int>& sum, vector<vector<int>>& dp) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r) return 0;
    int res = INF;
    for (int i = l; i < r; i++) {
        res = min(res, solve(l, i, sum, dp) + solve(i + 1, r, sum, dp) + calc(sum[i] - sum[l - 1], sum[r] - sum[i]));
    }
    return dp[l][r] = res;
}

int baseline(int N, vector<int>& t) {
    vector<int> sum(N + 1, 0);
    vector<vector<int>> dp(N + 1, vector<int>(N + 1, -1));
    for (int i = 1; i <= N; i++) {
        sum[i] = t[i] + sum[i - 1];
    }
    return solve(1, N, sum, dp);
}

vector<int> generateInput(int N) {
    vector<int> t(N + 1);
    for (int i = 1; i <= N; i++) {
        t[i] = i;
    }
    return t;
}