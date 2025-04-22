#pragma once

long long baseline(long long k) {
    long long x = 0, a = 1;
    while (k > 0) {
        x += a;
        a *= 2;
        k /= 2;
    }
    return x;
}

long long generateInput() {
    return 1000000000000LL; // A large value to test computational efficiency.
}