#pragma once

#include<vector>
#include<string>

std::pair<int, int> baseline(const std::string& s) {
    int len = s.length();
    if (len < 2) {
        return {-1, -1};
    }
    for (int i = 0; i < len - 1; i++) {
        if (s[i] == s[i + 1]) {
            return {i + 1, i + 2};
        } else if (i < len - 2 && s[i] == s[i + 2]) {
            return {i + 1, i + 3};
        }
    }
    return {-1, -1};
}

std::string generateInput() {
    return std::string(1000000, 'a');
}