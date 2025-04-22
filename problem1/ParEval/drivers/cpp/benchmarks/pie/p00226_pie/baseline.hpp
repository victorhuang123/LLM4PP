#pragma once

#include <string>
#include <vector>
#include <utility>

std::pair<int, int> baseline(const std::string& r, const std::string& a) {
    int f[2] = {0, 0};
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 0; j--) {
            if (a[i] == r[j]) {
                f[i != j]++;
            }
        }
    }
    return {f[0], f[1]};
}

std::pair<std::string, std::string> generate_input() {
    return {"abcd", "dcba"};
}