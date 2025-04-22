#pragma once

#include<vector>
#include<functional>

using namespace std;

int baseline(int n, int s) {
    vector<vector<int>> memo(1024, vector<int>(1000, -1));

    if (n > 10 || s >= 1000) {
        return 0;
    }

    function<int(int, int, int)> search = [&](int stat, int sum, int dep) {
        if (dep == n) return memo[stat][sum] = (s == sum);
        if (memo[stat][sum] != -1) return memo[stat][sum];

        int cnt = 0;
        for (int i = 0; i < 10; i++) {
            if ((stat & (1 << i)) == 0) {
                stat |= 1 << i;
                cnt += search(stat, sum + i * (n - dep), dep + 1);
                stat &= ~(1 << i);
            }
        }
        return memo[stat][sum] = cnt;
    };

    return search(0, 0, 0);
}