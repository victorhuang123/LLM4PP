#pragma once

#include <vector>

int baseline(int a, const std::vector<int>& arr1, const std::vector<int>& temp, const std::vector<int>& arr2) {
    int ans = 0;
    for (int i = 0; i < a; i++) {
        ans += temp[i];
    }
    for (int i = 0; i < a - 1; i++) {
        if (arr1[i] == arr1[i + 1] - 1) {
            ans += arr2[arr1[i]];
        }
    }
    return ans;
}

std::vector<int> generateInput(int a) {
    std::vector<int> arr1(a);
    std::vector<int> temp(a, 1);
    std::vector<int> arr2(a, 1);
    for (int i = 0; i < a; i++) {
        arr1[i] = i;
    }
    return {a, arr1, temp, arr2};
}