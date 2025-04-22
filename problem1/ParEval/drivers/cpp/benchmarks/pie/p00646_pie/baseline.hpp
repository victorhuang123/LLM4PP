#pragma once

#include <vector>

using namespace std;

typedef long long lint;

lint baseline(lint L) {
    vector<int> cn;
    int k = 0;

    for (int i = 2; (lint)i * i <= L; i++) {
        if (L % i == 0) {
            cn.push_back(0);
            while (L % i == 0) {
                L /= i;
                cn[k]++;
            }
            k++;
        }
    }

    if (L > 1) cn.push_back(1);

    lint ans = 1;
    for (int i = 0; i < cn.size(); i++) {
        ans *= (2 * cn[i] + 1);
    }

    return (ans / 2 + 1);
}

lint generateInput() {
    return 999999999999999999LL; // A large number to maximize problem scale
}