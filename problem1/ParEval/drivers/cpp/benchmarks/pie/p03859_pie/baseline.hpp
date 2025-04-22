#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef pair<pii, int> piipi;
typedef pair<pii, pii> piipii;

#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define eb emplace_back

const int mod = 1000000007;

int baseline(int n, int m, const vector<char>& s, const vector<int>& l, const vector<int>& r) {
    vector<int> mx(n + 1);
    vector<vector<int>> sum(n + 1, vector<int>(2, 0));
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= n; i++) mx[i] = i;
    for(int i = 1; i <= m; i++) {
        mx[l[i]] = max(mx[l[i]], r[i]);
    }

    for(int i = 1; i <= n; i++) {
        sum[i][s[i] - '0']++;
        sum[i][0] += sum[i - 1][0];
        sum[i][1] += sum[i - 1][1];
    }

    for(int i = 1; i <= n; i++) mx[i] = max(mx[i], mx[i - 1]);

    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            if(dp[i - 1][j]) {
                int c0 = sum[mx[i]][0] - j;
                int c1 = sum[mx[i]][1] - (i - 1 - j);
                if(c0 > 0) dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j]) % mod;
                if(c1 > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            }
        }
    }

    int ans = 0;
    for(int j = 0; j <= n; j++) ans = (ans + dp[n][j]) % mod;
    return ans;
}

vector<char> generateInputS(int n) {
    vector<char> s(n + 1);
    for(int i = 1; i <= n; i++) {
        s[i] = '0' + (rand() % 2);
    }
    return s;
}

vector<int> generateInputLR(int m, int n) {
    vector<int> l(m + 1), r(m + 1);
    for(int i = 1; i <= m; i++) {
        l[i] = 1 + rand() % n;
        r[i] = l[i] + rand() % (n - l[i] + 1);
    }
    return l, r;
}