#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long LL;

LL baseline(LL n, LL m, vector<vector<char>>& ch) {
    vector<vector<LL>> dp(n + 1, vector<LL>(m + 1, LLONG_MAX));

    if (ch[1][1] == '.') dp[1][1] = 0;
    else dp[1][1] = 1;

    for (LL i = 1; i <= n; i++) {
        for (LL j = 1; j <= m; j++) {
            if (i > 1) {
                if (ch[i][j] == ch[i - 1][j]) dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                if (ch[i][j] != ch[i - 1][j]) dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            }
            if (j > 1) {
                if (ch[i][j] == ch[i][j - 1]) dp[i][j] = min(dp[i][j], dp[i][j - 1]);
                if (ch[i][j] != ch[i][j - 1]) dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            }
        }
    }

    if (ch[n][m] == '#') dp[n][m]++;
    dp[n][m] >>= 1;
    return dp[n][m];
}

vector<vector<char>> generateInput(LL n, LL m) {
    vector<vector<char>> ch(n + 1, vector<char>(m + 1));
    for (LL i = 1; i <= n; i++) {
        for (LL j = 1; j <= m; j++) {
            ch[i][j] = (i + j) % 2 == 0 ? '.' : '#';
        }
    }
    return ch;
}