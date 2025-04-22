#pragma once

#include <bits/stdc++.h>
using namespace std;

int baseline(long long n) {
    const int OO = 0x3f3f3f3f; // A large constant representing infinity
    int ans = OO;
    for (long long i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            int cnt1 = 0, cnt2 = 0;
            long long a = i, b = n / i;
            while (a) a /= 10, cnt1++;
            while (b) b /= 10, cnt2++;
            ans = min(ans, max(cnt1, cnt2));
        }
    }
    return ans;
}

long long generateInput() {
    return 999999999999999999LL; // Example input to maximize problem scale
}