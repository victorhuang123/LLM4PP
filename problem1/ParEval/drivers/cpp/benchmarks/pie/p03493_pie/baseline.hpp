#pragma once

#include <vector>
#include <iostream>

int baseline(int n, int m, int a, int b, const std::vector<char>& input) {
    int ans = 0;
    for (int i = 0; i < 3; i++) {
        if (input[i] == '1')
            ans++;
    }
    return ans;
}

std::vector<char> generateInput() {
    return {'1', '0', '1'};
}