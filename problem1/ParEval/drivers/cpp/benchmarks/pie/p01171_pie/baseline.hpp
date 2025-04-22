#pragma once

#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int baseline(int a, int b) {
    const int MAX = 1000000;
    vector<int> memo(MAX + 10, -1);

    auto key = [&](int n) -> int {
        if (memo[n] != -1)
            return memo[n];

        int sum = 0, last;
        for (int i = 2; i <= n; ++i) {
            if (n % i == 0) {
                sum += i, last = i;
                while (n % i == 0)
                    n /= i;
            }
        }
        return memo[n] = 2 * last - sum;
    };

    return key(a) > key(b) ? a : b;
}

vector<int> generate_input() {
    return {999983, 999979};  // Large primes to maximize computational load
}