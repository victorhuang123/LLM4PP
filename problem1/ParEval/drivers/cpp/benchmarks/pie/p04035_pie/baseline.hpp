#pragma once

#include <vector>
#include <iostream>

using namespace std;

using LL = long long;
using VL = vector<LL>;

VL generateInput(LL N, LL L) {
    VL a(N);
    for (LL i = 0; i < N; ++i) {
        a[i] = i + 1;
    }
    return a;
}

bool baseline(LL N, LL L, const VL& a) {
    LL pos = -1;
    for (LL i = 0; i < N - 1; ++i) {
        if (a[i] + a[i + 1] >= L) {
            pos = i;
        }
    }
    return pos != -1;
}