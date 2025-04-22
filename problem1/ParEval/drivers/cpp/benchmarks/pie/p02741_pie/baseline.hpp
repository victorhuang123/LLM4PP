#pragma once

#include<vector>
#include<algorithm>

int baseline(int T) {
    std::vector<int> element = {0, 1, 1, 1, 2, 1, 2, 1, 5, 2, 2, 1, 5, 1, 2, 1, 14, 1, 5, 1, 5, 2, 2, 1, 15, 2, 2, 5, 4, 1, 4, 1, 51};
    return element[T];
}

std::vector<int> generateInput() {
    std::vector<int> input;
    for (int i = 0; i < 1000000; ++i) {
        input.push_back(i % 32);
    }
    return input;
}