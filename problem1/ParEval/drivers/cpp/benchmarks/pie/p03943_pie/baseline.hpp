#pragma once

#include <algorithm>
#include <vector>

bool baseline(int a, int b, int c) {
    std::vector<int> arr = {a, b, c};
    std::sort(arr.begin(), arr.end());
    do {
        if (arr[0] + arr[1] == arr[2]) {
            return true;
        }
    } while (std::next_permutation(arr.begin(), arr.end()));
    return false;
}

std::vector<int> generateInput() {
    return {1000000, 2000000, 3000000};
}