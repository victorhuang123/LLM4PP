#pragma once

#include <vector>

int baseline(int n, const std::vector<std::vector<char>>& s) {
    int ans = 0, flag;

    for(int k = 0; k < n; k++) {
        flag = 1;
        for(int i = 0; i < n && flag; i++) {
            for(int j = 0; j < n; j++) {
                if(s[i][(j + k) % n] != s[j][(i + k) % n]) {
                    flag = 0;
                    break;
                }
            }
        }
        ans += n * flag;
    }
    return ans;
}

std::vector<std::vector<char>> generateInput(int n) {
    std::vector<std::vector<char>> s(n, std::vector<char>(n, 'a'));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            s[i][j] = 'a' + (i + j) % 26;
        }
    }
    return s;
}