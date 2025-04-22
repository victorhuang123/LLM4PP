#pragma once

#include <vector>
#include <string>
#include <cctype>

std::string baseline(const std::string& input) {
    std::string result;
    for (char ch : input) {
        if (islower(ch)) {
            result += toupper(ch);
        } else if (isupper(ch)) {
            result += tolower(ch);
        } else {
            result += ch;
        }
    }
    return result;
}

std::string generateInput() {
    std::string input;
    for (int i = 0; i < 1000000; ++i) {
        input += (i % 2 == 0) ? 'a' : 'A';
    }
    return input;
}