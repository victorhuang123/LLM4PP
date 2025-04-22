#pragma once

#include <string>

bool baseline(const std::string& s) {
    char first = s[0];
    char second = '\0';

    for (int i = 0; i < 4; i++) {
        if (first != s[i]) {
            second = s[i];
            break;
        }
    }

    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < 4; i++) {
        if (first == s[i]) {
            sum1 += 1;
        } else if (second == s[i]) {
            sum2 += 1;
        }
    }

    return (sum1 == 2 && sum2 == 2);
}

std::string generateInput() {
    return "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz";
}