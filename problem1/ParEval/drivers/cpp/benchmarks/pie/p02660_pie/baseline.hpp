#pragma once

#include <vector>

std::vector<int> generateInput() {
    return std::vector<int>(40, 1000000);
}

long long baseline(long long N) {
    const std::vector<int> e = {0,1,1,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,
                                5,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,8,8,8,8};
    int x;
    long long a = 0;

    x = 0;
    while (N % 2 == 0) {
        x++;
        N /= 2;
    }
    a += e[x];

    for (int i = 3; i <= 1e6; i += 2) {
        x = 0;
        while (!(N % i)) {
            x++;
            N /= i;
        }
        a += e[x];
    }

    if (N > 1) a++;

    return a;
}