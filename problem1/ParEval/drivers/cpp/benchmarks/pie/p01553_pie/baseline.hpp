#pragma once

#include <vector>

using namespace std;

#define MOD 1000000007

typedef long long ll;

ll baseline(int N, vector<char>& v) {
    if (N == 0) {
        return 1;
    }
    if (v[0] == 'D') {
        return 0;
    }

    vector<vector<vector<ll>>> dp(N, vector<vector<ll>>(N+1, vector<ll>(N+1, 0)));
    dp[0][1][1] = 1; // v[0] = 'U'
    for (int i = 0; i < N-1; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (v[i+1] == 'U') {
                    dp[i+1][j+1][k+1] = (dp[i+1][j+1][k+1] + dp[i][j][k]) % MOD;
                    if (j >= 1) {
                        dp[i+1][j][k] = (dp[i+1][j][k] + j * dp[i][j][k]) % MOD;
                    }
                }
                else { // D
                    if (k >= 1) {
                        dp[i+1][j][k] = (dp[i+1][j][k] + k * dp[i][j][k]) % MOD;
                        if (j >= 1) {
                            dp[i+1][j-1][k-1] = (dp[i+1][j-1][k-1] + j * k * dp[i][j][k]) % MOD;
                        }
                    }
                }
            }
        }
    }

    return dp[N-1][0][0];
}

vector<char> generateInput(int N) {
    vector<char> v(N, 'U');
    v[N-1] = 'D';
    return v;
}