#pragma once

#include <vector>

unsigned long long baseline(unsigned long long n) {
    unsigned long long ans = 0, k = 1;

    if (n & 1) {
        return 0;
    }

    ans = n / 10;
    while ((k *= 5) <= n) {
        ans += n / (k * 10);
    }

    return ans;
}

unsigned long long generateInput() {
    return 1000000000000000000ULL; // A large number to test efficiency
}