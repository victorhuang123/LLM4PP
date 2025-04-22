#pragma once

#include <bits/stdc++.h>

using namespace std;

using VI = vector<int>;

int baseline(int N) {
    VI a(4);
    for (int i = 0; i < 4; ++i) {
        a[i] = N / (int)pow(10, 3 - i);
        a[i] %= 10;
    }
    for (int op = 0; op < (1 << 3); ++op) {
        int ret = a[0];
        for (int i = 1; i < 4; ++i) {
            if (op & (1 << (i - 1))) {
                ret -= a[i];
            } else {
                ret += a[i];
            }
        }
        if (ret == 7) {
            return op;
        }
    }
    return -1;
}

VI generateInput() {
    return {9999};
}