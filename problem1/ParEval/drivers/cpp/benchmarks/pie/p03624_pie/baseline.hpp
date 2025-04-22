#pragma once

#include <vector>
#include <string>

std::string baseline(const std::string& s) {
    std::vector<int> a(26, 0);
    int l = s.length();
    for(int i = 0; i < l; i++) a[s[i]-'a'] = 1;
    for(int i = 0; i < 26; i++) {
        if(a[i] == 0) {
            return std::string(1, (char)(i + 'a'));
        }
    }
    return "None";
}

std::string generateInput() {
    return std::string(1000000, 'a'); // Generates a string with 1 million 'a's
}