#pragma once

#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 16e3 + 10;

int _dp[2][2 * N + 100], *dp[2];

void fill_dp(int indx, vector<int>& vec) {
    for (int i = -N + 1; i < N; i++)
        dp[1][i] = 0;
    dp[1][0] = 1;

    for (int i = 0; i < vec.size(); i++) {
        int now = (i & 1), prv = (now ^ 1), x = vec[i];
        for (int j = -N + 1; j < N; j++) {
            dp[now][j] = 0;
            if (j - x > -N)
                dp[now][j] = dp[prv][j - x];
            if (j + x < N)
                dp[now][j] = max(dp[now][j], dp[prv][j + x]);
        }
    }
}

bool baseline(string s, int x, int y) {
    dp[0] = _dp[0] + N + 50;
    dp[1] = _dp[1] + N + 50;

    while (s.size() && s.back() == 'T')
        s.pop_back();
    if (!s.size()) {
        return (!x && !y);
    }

    int tmp = 0, indx = 0;
    while (indx < s.size() && s[indx] == 'F')
        tmp++, indx++;

    int last = 0, num = 0;
    vector<int> vec[2];
    for (int i = indx; i < s.size(); i++) {
        if (s[i] == 'T')
            vec[num & 1].push_back(last), last = 0, num++;
        else
            last++;
    }
    vec[num & 1].push_back(last);

    fill_dp(0, vec[0]);
    if (!dp[((int)vec[0].size() & 1) ^ 1][x - tmp]) {
        return false;
    }
    fill_dp(1, vec[1]);
    return dp[((int)vec[1].size() & 1) ^ 1][y];
}

vector<int> generate_input() {
    vector<int> input;
    for (int i = 0; i < 16000; i++) {
        input.push_back(1);
    }
    return input;
}