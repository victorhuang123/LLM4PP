#pragma once

#include <vector>
#include <string>

std::string baseline(const std::string& str) {
    std::vector<int> cnt(130, 0);
    for (char ch : str) {
        int k = static_cast<int>(ch - 'a');
        cnt[k]++;
        if (cnt[k] > 1) {
            return "no";
        }
    }
    return "yes";
}

std::string generateInput() {
    std::string input;
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        input += ch;
    }
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        input += ch;
    }
    for (char ch = '0'; ch <= '9'; ++ch) {
        input += ch;
    }
    input += "!@#$%^&*()_+-=[]{}|;':\",./<>?`~";
    return input;
}