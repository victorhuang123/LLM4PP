#pragma once

#include <vector>
#include <algorithm>

using namespace std;

typedef long long signed int LL;
typedef long long unsigned int LU;

const int MOD = 1000000007;

LL f(LL x) {
    if(x == 0) { return 1; }
    return (x * f(x - 1)) % MOD;
}

int baseline(int n, int eor, const vector<int>& a) {
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(256, vector<int>(n + 1, 0)));
    dp[0][0][0] = 1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 256; j++) {
            for(int k = 0; k <= n; k++) {
                dp[i + 1][j][k] = (dp[i + 1][j][k] + dp[i][j][k]) % MOD;
                if(k < n) {
                    dp[i + 1][j ^ a[i]][k + 1] = (dp[i + 1][j ^ a[i]][k + 1] + dp[i][j][k]) % MOD;
                }
            }
        }
    }

    LL ans = 0;
    for(int k = 1; k <= n; k++) {
        ans = (ans + f(k) * dp[n][eor][k]) % MOD;
    }

    return ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        a[i] = i % 256;
    }
    return a;
}