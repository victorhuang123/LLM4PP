#pragma once

#include<vector>
#include<cstring>

#define N 50000

int baseline(int c) {
    std::vector<bool> prime(N, true);
    std::vector<int> primes;
    prime[0] = prime[1] = false;
    for (int x = 2; x < N; ++x) {
        if (prime[x]) {
            primes.push_back(x);
            for (int i = x + x; i < N; i += x) {
                prime[i] = false;
            }
        }
    }
    int cnt = 0;
    for (int x = 0; x < primes.size(); ++x) {
        for (int y = x; y < primes.size(); ++y) {
            if (primes[x] + primes[y] == c) cnt++;
            if (primes[x] + primes[y] > c) break;
        }
        if (primes[x] >= c) break;
    }
    return cnt;
}

std::vector<int> generateInput() {
    return {N};
}