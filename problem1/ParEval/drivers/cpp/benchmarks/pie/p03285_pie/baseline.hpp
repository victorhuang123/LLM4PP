#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<long long> generateInput() {
    return {1000000000000LL};
}

bool baseline(long long n) {
    bool fl = false;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            long long pos = 4 * i + 7 * j;
            if (pos == n) {
                fl = true;
                break;
            }
        }
        if (fl) break;
    }
    return fl;
}