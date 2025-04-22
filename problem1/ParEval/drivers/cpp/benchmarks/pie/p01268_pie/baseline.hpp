#pragma once

#include<vector>
#include<algorithm>

bool is(int x) {
    for (int i = 2; i * i <= x; i++) if (x % i == 0) return false;
    return true;
}

int baseline(int n, int p) {
    int cnt = 0;
    n++;
    if (n == 1) n++;
    std::vector<int> primes;
    std::vector<int> sums;
    while (true) {
        if (is(n)) {
            cnt++;
            primes.push_back(n);
        }
        if (cnt == 78) break;
        n++;
    }
    for (int i = 0; i < primes.size(); i++) {
        for (int j = 0; j < primes.size(); j++) {
            if (j > primes.size()) break;
            if (i < j) break;
            sums.push_back(primes[i] + primes[j]);
        }
    }
    std::sort(sums.begin(), sums.end());
    return sums[p - 1];
}

std::pair<int, int> generate_input() {
    return {1000000, 1000};
}