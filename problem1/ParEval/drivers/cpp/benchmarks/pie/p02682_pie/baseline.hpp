#pragma once

#include <vector>
#include <algorithm>

long long int baseline(long long int a, long long int b, long long int c, long long int k) {
    long long int sum = 0;

    while (k > 0) {
        if (k - a <= 0 && a > 0) {
            sum = k;
            break;
        } else if (k - a > 0 && a > 0) {
            sum += a;
            k -= a;
            a = -1;
        } else if (k - b <= 0 && b > 0) {
            b = -1;
            break;
        } else if (k - b > 0 && b > 0) {
            k -= b;
            b = -1;
        } else if (k - c <= 0 && c > 0) {
            sum -= k;
            break;
        } else if (k - c >= 0 && c > 0) {
            sum -= c;
            break;
        } else {
            break;
        }
    }

    return sum;
}

std::vector<long long int> generateInput() {
    return {1000000000000LL, 1000000000000LL, 1000000000000LL, 1000000000000LL};
}