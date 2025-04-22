#pragma once

#include <vector>
#include <algorithm>
#include <string>

int baseline(const std::string& s, const std::string& t) {
    int lt = t.length();
    int ls = s.length();
    int ans = 0x7fffffff;

    for (int i = 0; i <= ls - lt; i++) {
        int tt = 0;
        for (int j = 0; j < lt; j++) {
            if (s[i + j] != t[j]) {
                tt++;
            }
        }
        ans = std::min(tt, ans);
    }
    return ans;
}

std::string generateExampleInput() {
    std::string s(1000000, 'a');
    std::string t(100000, 'b');
    return s + t;
}