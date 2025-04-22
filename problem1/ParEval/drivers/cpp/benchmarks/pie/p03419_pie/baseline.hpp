#pragma once

#include <vector>
#include <cmath>

int baseline(int n, int m) {
    return abs(n - 2) * abs(m - 2);
}

std::vector<int> generateInput() {
    std::vector<int> input;
    input.push_back(1000000); // n
    input.push_back(1000000); // m
    return input;
}