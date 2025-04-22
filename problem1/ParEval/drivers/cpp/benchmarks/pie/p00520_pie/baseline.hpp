#pragma once

#include<bits/stdc++.h>

using namespace std;

int h(vector<int>& v) {
    int p = 1, res = 0;
    for (int i : v) res += p * i, p *= 7;
    return res;
}

int baseline(int n, vector<int>& d, vector<int>& a) {
    vector<int> id(1000000);
    vector<vector<int>> re(5040);
    vector<vector<int>> dp(100, vector<int>(5040));

    vector<int> v(7); iota(v.begin(), v.end(), 0);
    int p = 0;

    do {
        id[h(v)] = p; re[p] = v;
        int cnt = 0;
        bool t[7]{};
        for (int i : v) {
            for (int j = 0; j < 7; j++) {
                if (t[j] && abs(j - i) <= d[j]) cnt += a[j];
            }
            t[i] = 1;
        }
        dp[0][p] = cnt;
        p++;
    } while (next_permutation(v.begin(), v.end()));

    int ans = 0;
    for (int i = 1; i + 6 < n; i++) {
        for (int j = 0; j < 5040; j++) {
            for (int k = 0; k < 8; k++) {
                auto t = re[j].begin();
                int cnt = 0, o = 0;
                bool p[8]{};
                vector<int> q(7);
                for (int l = 0; l < 8; l++) {
                    if (k == l) {
                        for (int y = 0; y < 8; y++) {
                            if (p[y] && y + d[i - 1 + y] >= 7)
                                cnt += a[i - 1 + y];
                        }
                        p[7] = 1; q[o++] = 6;
                    } else {
                        if (p[7] && 7 - d[i + 6] <= *t) cnt += a[i + 6];
                        p[*t] = 1;
                        if (*t) q[o++] = *t - 1;
                        t++;
                    }
                }
                int v = id[h(q)];
                dp[i][v] = max(dp[i][v], dp[i - 1][j] + cnt);
                ans = max(ans, dp[i][v]);
            }
        }
    }
    return ans;
}

vector<int> generateInput(int n) {
    vector<int> d(n), a(n);
    for (int i = 0; i < n; i++) {
        d[i] = rand() % 7;
        a[i] = rand() % 100;
    }
    return d, a;
}