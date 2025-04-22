#pragma once

#include <vector>
#include <cmath>

std::vector<long long> generateInput() {
    std::vector<long long> input = {1000000, 500000, 250000, 125000, 62500, 31250, 15625, 7812, 3906, 1953};
    return input;
}

long long baseline(long long max_num) {
    std::vector<bool> flag(max_num + 1, false);
    long long i, j, p, count;

    p = static_cast<long long>(std::sqrt(max_num));

    for (i = 3; i <= p; i += 2) {
        if (!flag[i]) {
            for (j = i * i; j <= max_num; j += 2 * i) {
                flag[j] = true;
            }
        }
    }

    count = 1; // 2 is prime
    for (i = 3; i <= max_num; i += 2) {
        if (!flag[i]) {
            count++;
        }
    }

    return count;
}