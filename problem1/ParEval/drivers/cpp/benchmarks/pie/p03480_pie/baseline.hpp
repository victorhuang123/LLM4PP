#pragma once

#include<vector>
#include<string>
#include<algorithm>

int baseline(const std::string& S) {
    int res = S.size();
    int a = S.size();
    for (int i = 1; i < S.size(); i++) {
        if (S[i] != S[i - 1])
            res = std::min(res, std::max(i, a - i));
    }
    return res;
}

std::string generateInput() {
    return std::string(1000000, 'a') + std::string(1000000, 'b');
}