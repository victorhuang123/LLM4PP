#pragma once

#include <vector>

const int MAX_X = 10000;

int baseline(int n) {
    std::vector<int> prime(MAX_X + 1, 1);

    for (int i = 2; i * i <= MAX_X; i++) {
        if (prime[i]) {
            for (int k = 2 * i; k <= MAX_X; k += i) {
                prime[k] = 0;
            }
        }
    }

    for (int i = n; i >= 2; i--) {
        if (prime[i] && prime[i - 2]) {
            return i - 2;
        }
    }

    return -1; // No twin primes found
}

int generateExampleInput() {
    return 10000;
}