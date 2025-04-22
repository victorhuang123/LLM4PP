#pragma once

#include <vector>

unsigned long long baseline(int n) {
    std::vector<unsigned long long> arrAns(46, 0);
    arrAns[0] = 2;
    for (int i = 1; i <= 45; ++i) {
        arrAns[i] = arrAns[i - 1] * 2 + 2;
    }
    return arrAns[n];
}

std::vector<int> generateInput() {
    return {45};
}