#pragma once

#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int baseline(int N, const vector<int>& s) {
    int dp[110][10010];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= 10000; ++j) {
            if (dp[i][j] == 0) continue;
            dp[i + 1][j] = 1;
            dp[i + 1][j + s[i]] = 1;
        }
    }

    int ans = 0;
    for (int i = 0; i <= 10000; ++i) {
        if (dp[N][i] == 1) {
            if (i % 10 != 0) {
                ans = max(ans, i);
            }
        }
    }

    return ans;
}

vector<int> generateInput(int N) {
    vector<int> s(N);
    for (int i = 0; i < N; ++i) {
        s[i] = i + 1;
    }
    return s;
}