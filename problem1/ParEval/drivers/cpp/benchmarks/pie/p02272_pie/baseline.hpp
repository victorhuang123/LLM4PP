#pragma once

#include <vector>
#include <algorithm>

#define INFTY 2000000000

int baseline(const std::vector<int>& A) {
    std::vector<int> arr = A;
    int cnt = 0;

    auto merge = [&](int left, int mid, int right) {
        int n1 = mid - left;
        int n2 = right - mid;
        std::vector<int> L(n1 + 1), R(n2 + 1);
        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int i = 0; i < n2; i++) R[i] = arr[mid + i];
        L[n1] = INFTY;
        R[n2] = INFTY;
        int i = 0, j = 0;
        for (int k = left; k < right; k++) {
            cnt++;
            if (L[i] <= R[j]) {
                arr[k] = L[i++];
            } else {
                arr[k] = R[j++];
            }
        }
    };

    auto mergeSort = [&](auto&& self, int left, int right) -> void {
        if (left + 1 < right) {
            int mid = (left + right) / 2;
            self(self, left, mid);
            self(self, mid, right);
            merge(left, mid, right);
        }
    };

    mergeSort(mergeSort, 0, arr.size());
    return cnt;
}

std::vector<int> generateInput() {
    std::vector<int> input(500000);
    for (int i = 0; i < 500000; ++i) {
        input[i] = 500000 - i;
    }
    return input;
}