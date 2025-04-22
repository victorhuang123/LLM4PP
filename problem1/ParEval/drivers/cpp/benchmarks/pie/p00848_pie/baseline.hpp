#pragma once

#include <vector>
#include <bitset>

int baseline(int n, int k) {
    bitset<1121> isprime;
    isprime.set();
    isprime.reset(0);
    isprime.reset(1);

    for(int i = 2; i * i <= 1120; ++i){
        if(isprime[i]){
            for(int j = i * i; j <= 1120; j += i){
                isprime.reset(j);
            }
        }
    }

    vector<int> prime;
    prime.reserve(200);
    for(int i = 2; i < 1120; ++i){
        if(isprime[i]){
            prime.push_back(i);
        }
    }

    prime.push_back(1e9);

    vector<vector<int> > dp(k + 1, vector<int>(n + 1));
    dp[0][0] = 1;

    for(auto it = prime.begin(); *it <= n; ++it){
        for(int j = n - *it; j >= 0; --j){
            for(int i = 0; i < k; ++i){
                dp[i + 1][j + *it] += dp[i][j];
            }
        }
    }

    return dp[k][n];
}

vector<int> generateInput() {
    return {1120, 14};
}