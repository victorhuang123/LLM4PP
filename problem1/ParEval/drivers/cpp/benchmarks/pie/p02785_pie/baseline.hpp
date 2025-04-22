#pragma once

#include <vector>
#include <algorithm>

unsigned long long baseline(unsigned long long n, unsigned long long k, const std::vector<unsigned long long>& arr) {
    unsigned long long cnt = 0;
    unsigned long long maxm = 1;

    for (int i = 0; i < n; i++) {
        cnt += arr[i];
    }
    std::vector<unsigned long long> sortedArr = arr;
    std::sort(sortedArr.begin(), sortedArr.end());

    if (k >= n) {
        return 0;
    } else if (k == 0) {
        return cnt;
    } else {
        for (int i = n - 1; i >= 0; i--) {
            if (maxm <= k) {
                cnt -= sortedArr[i];
            }
            maxm++;
        }
        return cnt;
    }
}

std::vector<unsigned long long> generateInput(unsigned long long n) {
    std::vector<unsigned long long> arr(n);
    for (unsigned long long i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}