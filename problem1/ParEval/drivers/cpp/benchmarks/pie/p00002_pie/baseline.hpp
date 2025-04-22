#pragma once

#include <vector>
#include <string>

int baseline(int a, int b) {
    int sum = a + b;
    int intLength = 0;
    while (sum != 0) {
        sum /= 10;
        intLength += 1;
    }
    return intLength;
}

std::vector<int> generateInput() {
    return {999999999, 999999999};
}