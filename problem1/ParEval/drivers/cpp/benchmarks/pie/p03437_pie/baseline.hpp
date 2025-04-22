#pragma once

#include<vector>
#include<cmath>

long long baseline(long long x, long long y) {
    long long g = 1, i, N = 1000000000000000000;
    int flag = 0;

    if (x % y == 0) flag = 0;
    else {
        for (i = 2; g < N; i++) {
            g = i * x;
            if (g % y != 0) {
                flag = 1;
                break;
            }
        }
    }

    if (flag) return g;
    else return -1;
}

std::vector<long long> generateInput() {
    return {999999999999999999, 999999999999999997};
}