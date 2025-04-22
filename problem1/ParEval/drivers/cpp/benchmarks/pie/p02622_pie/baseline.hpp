#pragma once

#include <vector>
#include <string>

std::vector<std::string> generateInput() {
    std::vector<std::string> input;
    std::string s(1000000, 'a');
    std::string t(1000000, 'b');
    input.push_back(s);
    input.push_back(t);
    return input;
}

int baseline(const std::string& s, const std::string& t) {
    int j = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != t[i]) {
            j++;
        }
    }
    return j;
}