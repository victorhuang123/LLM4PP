#pragma once

#include <vector>

using namespace std;

long long baseline(long long x, long long y) {
    vector<long long> ar(1000000, -1);
    long long rem, temp, i, j, total, f = 0;

    temp = x;
    i = 0;

    while (temp >= 1) {
        rem = temp % y;
        temp = temp / y;
        ar[i] = rem;
        i++;
    }

    for (j = 0; j < i; j++) {
        total = ar[j] % 10;
        f++;
    }

    return f;
}

vector<long long> generateInput() {
    return {999999999999999999LL, 2LL};
}