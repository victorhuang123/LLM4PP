#pragma once

#include <vector>
#include <string>

std::string baseline(const std::string& s1, const std::string& s2, const std::string& s3) {
    std::string s = s1 + ' ' + s2 + ' ' + s3;
    std::string result;
    result += (char)(s[0] - 32);
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            result += (char)(s[i + 1] - 32);
        }
    }
    return result;
}

std::vector<std::string> generateInput() {
    return {"abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"};
}