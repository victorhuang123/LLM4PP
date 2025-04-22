#pragma once

#include <vector>
#include <string>
#include <algorithm>

std::string baseline(std::string s, std::string t) {
    std::reverse(s.begin(), s.end());
    std::reverse(t.begin(), t.end());
    int Ns = s.size();
    int Nt = t.size();
    bool now = false;

    for (int i = 0; i < Ns - Nt + 1; i++) {
        bool ok = true;
        for (int j = 0; j < Nt; j++) {
            if (s[i + j] != t[j] && s[i + j] != '?') {
                ok = false;
                break;
            }
        }
        if (ok) {
            for (int j = 0; j < Nt; j++) {
                s[i + j] = t[j];
            }
            now = true;
            break;
        }
    }

    if (!now) {
        return "UNRESTORABLE";
    }

    for (int i = 0; i < Ns; i++) {
        if (s[i] == '?') s[i] = 'a';
    }

    std::reverse(s.begin(), s.end());
    return s;
}

std::pair<std::string, std::string> generate_input() {
    std::string s(100000, '?');
    std::string t(50000, 'a');
    return {s, t};
}