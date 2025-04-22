#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

const int inf = 0x3f3f3f3f;

int getval(const string& a, const string& b) {
    int la = a.length(), lb = b.length();

    for (int i = 0; i < la; i++)
        if (memcmp(&a[i], b.c_str(), lb) == 0) return 0;

    for (int len = min(la, lb); len > 0; len--) {
        int i, j;
        for (i = la - len, j = 0; j < len; i++, j++)
            if (a[i] != b[j]) break;
        if (j == len) return lb - len;
    }
    return lb;
}

int baseline(int N, const vector<string>& str) {
    vector<vector<int>> mp(N, vector<int>(N));
    vector<vector<int>> dp(1 << N, vector<int>(N, -1));
    vector<int> st(N);

    for (int i = 0; i < N; i++) {
        st[i] = 1 << i;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int t = getval(str[i], str[j]);
            if (t == 0) {
                st[i] |= 1 << j;
                mp[i][j] = 0;
            } else {
                mp[i][j] = t;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        dp[st[i]][i] = str[i].length();
    }

    for (int s = 0; s < (1 << N); s++) {
        for (int i = 0; i < N; i++) {
            if (dp[s][i] != -1) {
                for (int j = 0; j < N; j++) {
                    if (!(s & (1 << j))) {
                        int tmp = s | st[j];
                        if (dp[tmp][j] == -1) {
                            dp[tmp][j] = dp[s][i] + mp[i][j];
                        } else {
                            dp[tmp][j] = min(dp[tmp][j], dp[s][i] + mp[i][j]);
                        }
                    }
                }
            }
        }
    }

    int ans = inf;
    for (int i = 0; i < N; i++) {
        if (dp[(1 << N) - 1][i] != -1) {
            ans = min(dp[(1 << N) - 1][i], ans);
        }
    }
    return ans;
}

vector<string> generateInput() {
    vector<string> input(15);
    for (int i = 0; i < 15; i++) {
        input[i] = string(120, 'a' + i % 26);
    }
    return input;
}