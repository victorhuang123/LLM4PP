#pragma once

#include <vector>
#include <string>

std::string baseline(const std::string& c) {
    for (int i = 0; i < c.length() - 2; i++) {
        if (c[i] == c[i+1] && c[i+1] == c[i+2]) {
            return "Yes";
        }
    }
    return "No";
}

std::string generateInput() {
    return std::string(1000000, 'a'); // Generates a string with 1 million 'a' characters
}