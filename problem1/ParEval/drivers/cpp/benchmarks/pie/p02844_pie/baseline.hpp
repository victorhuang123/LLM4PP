#pragma once

#include <vector>
#include <set>
#include <string>

int baseline(int n, const std::string& str) {
    std::set<int> z1, z2, z3;
    for (int i = 0; i < n; i++) {
        int tmp = str[i] - '0';
        {
            auto it = z2.begin();
            for (; it != z2.end(); ++it) {
                z3.insert((*it) * 10 + tmp);
            }
        }
        {
            auto it = z1.begin();
            for (; it != z1.end(); ++it) {
                z2.insert((*it) * 10 + tmp);
            }
        }
        z1.insert(tmp);
    }
    return z3.size();
}

std::string generateInput(int n) {
    std::string str(n, '0');
    for (int i = 0; i < n; i++) {
        str[i] = '0' + (i % 10);
    }
    return str;
}