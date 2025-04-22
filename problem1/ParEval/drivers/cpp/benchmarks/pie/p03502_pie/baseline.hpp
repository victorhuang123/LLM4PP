#pragma once

#include <vector>

long long generateInput() {
    return 999999999999999999LL; // A large number to maximize computational load
}

bool baseline(long long value) {
    int divisor = 0;
    long long temp = value;
    while (temp != 0) {
        divisor += temp % 10;
        temp /= 10;
    }
    return value % divisor == 0;
}