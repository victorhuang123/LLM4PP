#pragma once

#include <vector>
#include <cmath>

int baseline(long long a, long long n, long long m) {
    long long R_ans, L_sum;
    int ans = 0, i = 1;

    R_ans = powl(i + a, n);

    while(R_ans <= m) {
        int num = R_ans;
        L_sum = 0;

        while(num > 0) {
            L_sum += num % 10;
            num /= 10;
        }

        if(R_ans == powl(L_sum + a, n)) ans++;
        i++;
        R_ans = powl(i + a, n);
    }

    return ans;
}

std::vector<long long> generateInput() {
    return {1000000000, 10, 1000000000000};
}