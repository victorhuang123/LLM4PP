#pragma once

#include <bits/stdc++.h>

using namespace std;

long long baseline(int K) {
    long long pw[20];
    pw[0] = 1;
    for (int i = 1; i < 20; i++) pw[i] = pw[i - 1] * 10;

    long long now = 0;
    while (K--) {
        now++;
        auto nxt = now, nxt_sum = 0LL;
        {
            auto buf = now;
            while (buf) nxt_sum += buf % 10, buf /= 10;
        }
        for (int i = 1; i < 18; i++) if (now >= pw[i]) {
            auto cur = now / pw[i] * pw[i] + pw[i] - 1;
            auto sum = 0LL, buf = cur;
            while (buf) sum += buf % 10, buf /= 10;
            if ((long long)cur * nxt_sum < (long long)nxt * sum) {
                nxt = cur, nxt_sum = sum;
            }
        }
        now = nxt;
    }
    return now;
}

int generateInput() {
    return 1000000; // Example input to maximize the problem scale
}