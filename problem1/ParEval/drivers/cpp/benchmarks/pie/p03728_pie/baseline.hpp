#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<long long int> generateInput(long long int N) {
    vector<long long int> p(364364);
    iota(p.begin(), p.end(), 1);
    return p;
}

long long int baseline(long long int N, vector<long long int>& p, vector<long long int>& id) {
    vector<long long int> dp(364364);
    long long int x, i;

    for(i = 0; i < N; ++i) {
        id[p[i]] = i;
    }

    dp[N] = 0;
    x = N;

    for(i = N - 1; i > 0; --i) {
        if(dp[i + 1]) {
            dp[i] = dp[i + 1];
            if((id[i] < id[i + 1]) ^ (id[i + 1] < id[x]) ^ (id[x] < id[i])) {
                ++dp[i];
                x = i + 1;
            }
        } else {
            dp[i] = dp[i + 1] + ((id[i] > id[i + 1]) ? 1 : 0);
            if(id[i] < id[i + 1]) --x;
        }
    }

    return dp[1];
}