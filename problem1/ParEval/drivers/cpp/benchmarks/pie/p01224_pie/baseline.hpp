#pragma once

#include <vector>
#include <cmath>

std::string baseline(long long n) {
    if (n == 1) {
        return "deficient number";
    }

    long long total = 1;
    long long a = 0;

    for (int i = 2; a != i && i <= sqrt(n); i++) {
        if (n % i == 0) {
            total += i;
            if (i != n / i) {
                total += (n / i);
            }
            a = n / i;
        }
        if (total > n) break;
    }

    if (n == total) return "perfect number";
    if (n < total) return "abundant number";
    return "deficient number";
}

std::vector<long long> generateInput() {
    return {999999999999999999LL};
}