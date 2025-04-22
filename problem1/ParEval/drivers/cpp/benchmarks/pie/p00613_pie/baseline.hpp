#pragma once

#include <vector>

int baseline(int k, const std::vector<int>& input) {
    int s = 0;
    for (int i = 0; i < k * (k - 1) / 2; i++) {
        s += input[i];
    }
    return s / (k - 1);
}

std::vector<int> generateInput(int k) {
    std::vector<int> input(k * (k - 1) / 2);
    for (int i = 0; i < k * (k - 1) / 2; i++) {
        input[i] = i + 1; // Example input values
    }
    return input;
}