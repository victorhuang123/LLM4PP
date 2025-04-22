#pragma once

#include <vector>

constexpr int MOD = 1e9 + 7;

long baseline(long L, long R) {
    std::vector<std::vector<std::vector<std::vector<long>>>> dp(66, std::vector<std::vector<std::vector<long>>>(2, std::vector<std::vector<long>>(2, std::vector<long>(2, 0))));
    dp[0][0][0][0] = 1;

    bool x[3] = {1, 0, 0}, y[3] = {1, 1, 0};

    for(int i = 0; i < 60; ++i) {
        bool lb = L>>(59-i)&1, rb = R>>(59-i)&1;

        for(int l = 0; l < 2; ++l) {
            for(int r = 0; r < 2; ++r) {
                for(int j = 0; j < 2; ++j) {
                    for(int k = 0; k < 3; ++k) {
                        if(!l && !x[k] && lb) continue;
                        if(!r && y[k] && !rb) continue;
                        if(!j && x[k] ^ y[k]) continue;

                        int nl = (x[k] ^ lb   ? 1 : l);
                        int nr = (y[k] ^ rb   ? 1 : r);
                        int nj = (x[k] & y[k] ? 1 : j);

                        (dp[i+1][nl][nr][nj] += dp[i][l][r][j]) %= MOD;
                    }
                }
            }
        }
    }

    long ans = 0;
    for(int l=0;l<2;++l) for(int r=0;r<2;++r) ans = (ans + dp[60][l][r][1]) % MOD;

    return ans;
}

std::pair<long, long> generateInput() {
    return {0, (1LL << 60) - 1};
}