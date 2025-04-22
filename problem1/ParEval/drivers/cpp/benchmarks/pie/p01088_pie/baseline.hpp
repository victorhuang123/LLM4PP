#pragma once

#include <vector>
#include <algorithm>

int baseline(const std::vector<int>& P) {
    int n = P.size();
    std::vector<std::vector<int>> dp(128, std::vector<int>(1024, -1));

    dp[0][0] = 0;

    for(int i = 0; i < n; ++i) {
        for(int j = n-1; j >= 0; --j) {
            for(int k = 1024 - 1; k >= 0; --k) {
                if( dp[j][k] == -1 ) continue;

                int n1kyen = (P[i] + 999) / 1000;
                int rem = dp[j][k] + n1kyen * 1000 - P[i];
                int next_num500yen = j + (rem >= 500 ? 1 : 0);
                int next_num1kyen  = k + n1kyen;
                int next_rem       = rem >= 500 ? rem - 500 : rem;

                int& next = dp[next_num500yen][next_num1kyen];
                next = std::max(next, next_rem);
            }
        }
    }

    int res = (1 << 28);
    int max = -1;

    for(int j = n; j >= 0; --j) {
        for(int k = 0; k < 1024; ++k) {
            if( dp[j][k] == -1 ) continue;

            int cost = k * 1000 - 500 * j - dp[j][k];
            res = std::min(res, cost);
        }

        if( res != (1 << 28) ) {
            max = j;
            break;
        }
    }

    return res;
}

std::vector<int> generateInput() {
    std::vector<int> P(1000);
    for(int i = 0; i < 1000; ++i) {
        P[i] = rand() % 100000 + 1;
    }
    return P;
}