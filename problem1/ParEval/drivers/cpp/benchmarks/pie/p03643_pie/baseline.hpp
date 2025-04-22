#pragma once

#include <vector>
#include <iostream>

std::vector<double> generateInput() {
    std::vector<double> input;
    for (double i = 0; i < 1000000; ++i) {
        input.push_back(i);
    }
    return input;
}

std::vector<std::string> baseline(const std::vector<double>& input) {
    std::vector<std::string> result;
    for (double a : input) {
        result.push_back("ABC" + std::to_string(a));
    }
    return result;
}