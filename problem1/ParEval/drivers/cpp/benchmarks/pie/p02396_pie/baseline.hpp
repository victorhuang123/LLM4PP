#pragma once

#include <vector>

std::vector<std::pair<int, int>> baseline(const std::vector<int>& input) {
    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == 0) break;
        result.emplace_back(i + 1, input[i]);
    }
    return result;
}

std::vector<int> generateInput() {
    std::vector<int> input(1000000, 1);
    input.back() = 0;
    return input;
}