#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(const string& s, const string& t) {
    int dp[100005][30];
    int vis[30];
    memset(dp, 0x3f, sizeof(dp));
    memset(vis, 0, sizeof(vis));

    for (int i = 0; i < s.length(); i++) {
        vis[s[i] - 'a'] = 1;
    }

    for (int i = s.length() - 2; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            dp[i + 1][j] = dp[i + 2][j];
        }
        dp[i + 1][s[i + 1] - 'a'] = i + 2;
    }

    for (int j = 0; j < 26; j++) {
        dp[0][j] = dp[1][j];
    }
    dp[0][s[0] - 'a'] = 1;

    long long nowl = 0, nowr = 0;
    for (int i = 0; i < t.length(); i++) {
        if (!vis[t[i] - 'a']) {
            return -1;
        }
        if (dp[nowl][t[i] - 'a'] == 0x3f3f3f3f) {
            nowr++;
            nowl = dp[0][t[i] - 'a'];
        } else {
            nowl = dp[nowl][t[i] - 'a'];
        }
    }
    return nowl + nowr * s.length();
}

vector<string> generateInput() {
    string s(100000, 'a');
    string t(100000, 'a');
    for (int i = 0; i < 100000; i++) {
        s[i] = 'a' + (i % 26);
        t[i] = 'a' + (i % 26);
    }
    return {s, t};
}