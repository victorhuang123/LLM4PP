#pragma once

#include <vector>
#include <algorithm>
#include <climits>

int64_t baseline(int64_t n, int64_t s) {
    auto Function = [](int64_t b, int64_t n) -> int64_t {
        int64_t sum = 0;
        while (n > 0) {
            sum += n % b;
            n /= b;
        }
        return sum;
    };

    if (n == s) {
        return n + 1;
    }
    for (int64_t b = 2; b <= n / b; b++) {
        if (Function(b, n) == s) {
            return b;
        }
    }
    if (s > n) {
        return -1;
    }
    int64_t ans = LLONG_MAX;
    for (int64_t x = 1; x <= (n - s) / x; x++) {
        if ((n - s) % x == 0) {
            const int64_t b = (n - s) / x + 1;
            if (Function(b, n) == s) {
                ans = std::min(ans, b);
            }
        }
    }
    if (ans == LLONG_MAX) {
        ans = -1;
    }
    return ans;
}