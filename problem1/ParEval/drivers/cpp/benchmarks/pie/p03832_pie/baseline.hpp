#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

ll mod = 1e9 + 7;

ll modpow(ll A, ll B) {
    if (B == 0) return 1;
    if (B % 2) return A * modpow(A, B - 1) % mod;
    ll half = modpow(A, B / 2);
    return half * half % mod;
}

ll baseline(int N, int A, int B, int C, int D) {
    vector<ll> F(1001), FI(1001);
    F[0] = 1;
    rep1(i, 1000) {
        F[i] = F[i - 1] * i % mod;
    }
    FI[1000] = modpow(F[1000], mod - 2);
    for (int i = 1000; i > 0; i--) {
        FI[i - 1] = FI[i] * i % mod;
    }

    vector<vector<ll>> dp(1001, vector<ll>(1001, 0));
    dp[0][0] = F[N];
    rep(i, N) {
        rep(j, N) {
            if (dp[i][j]) {
                dp[i + 1][j] += dp[i][j];
                dp[i + 1][j] %= mod;
                if (A <= i + 1 && i + 1 <= B) {
                    for (int k = C; k <= D; k++) {
                        int kari = j + k * (i + 1);
                        if (kari <= N) {
                            dp[i + 1][kari] += dp[i][j] * modpow(FI[i + 1], k) % mod * FI[k] % mod;
                            dp[i + 1][kari] %= mod;
                        }
                        else break;
                    }
                }
            }
        }
    }
    ll kotae = 0;
    rep(i, N + 1) {
        kotae += dp[i][N];
        kotae %= mod;
    }
    return kotae;
}

vector<int> generateInput() {
    return {1000, 1, 1000, 1, 1000};
}