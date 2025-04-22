#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

ll baseline(ll N, ll M, vector<ll>& S, vector<ll>& T) {
    vector<vector<ll>> dp(N + 1, vector<ll>(M + 1, 0));
    dp[0][0] = 1;

    vector<ll> sb(N, -1), tb(M, -1);
    vector<ll> pos(100010, -1);

    for(ll i = 0; i < N; i++){
        if(pos[S[i]] == -1){
            sb[i] = -1;
        }else{
            sb[i] = pos[S[i]];
        }
        pos[S[i]] = i;
    }

    fill(pos.begin(), pos.end(), -1);
    for(ll i = 0; i < M; i++){
        if(pos[T[i]] == -1){
            tb[i] = -1;
        }else{
            tb[i] = pos[T[i]];
        }
        pos[T[i]] = i;
    }

    for(ll i = 1; i <= N; i++){
        dp[i][0] = 1;
    }

    for(ll i = 1; i <= M; i++){
        dp[0][i] = 1;
    }

    for(ll i = 0; i < N; i++){
        for(ll j = 0; j < M; j++){
            if(S[i] == T[j]){
                dp[i+1][j+1] = (dp[i+1][j] + dp[i][j+1]) % MOD;
            }else{
                dp[i+1][j+1] = (dp[i+1][j] + dp[i][j+1] - dp[i][j] + MOD) % MOD;
            }
        }
    }

    return dp[N][M];
}

vector<ll> generateInput(ll size) {
    vector<ll> input(size);
    for(ll i = 0; i < size; i++) {
        input[i] = i + 1;
    }
    return input;
}