#pragma once

#include <vector>

int baseline(int n, const std::vector<int>& memArray) {
    int cnt = 0;
    std::vector<int> a(100000, 0);

    for (int i = 0; i < n; ++i) {
        if (memArray[i] > 100000) cnt++;
        else a[memArray[i] - 1]++;
    }

    for (int i = 0; i < 100000; ++i) {
        if (a[i] < i + 1) cnt += a[i];
        else cnt += a[i] - (i + 1);
    }

    return cnt;
}

std::vector<int> generateInput(int n) {
    std::vector<int> memArray(n);
    for (int i = 0; i < n; ++i) {
        memArray[i] = (i % 100000) + 1;
    }
    return memArray;
}