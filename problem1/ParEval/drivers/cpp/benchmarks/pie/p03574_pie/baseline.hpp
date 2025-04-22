#pragma once

#include<vector>
#include<string>

std::vector<std::string> generateInput(int n, int m) {
    std::vector<std::string> a(n + 2, std::string(m + 2, '.'));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if ((i + j) % 2 == 0) {
                a[i][j] = '#';
            }
        }
    }
    return a;
}

std::vector<std::string> baseline(int n, int m, const std::vector<std::string>& a) {
    std::vector<std::string> result(n, std::string(m, '0'));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j] == '#') {
                result[i-1][j-1] = '#';
            } else {
                int s = 0;
                if (a[i-1][j-1] == '#') s++;
                if (a[i-1][j] == '#') s++;
                if (a[i-1][j+1] == '#') s++;
                if (a[i][j+1] == '#') s++;
                if (a[i+1][j+1] == '#') s++;
                if (a[i+1][j] == '#') s++;
                if (a[i+1][j-1] == '#') s++;
                if (a[i][j-1] == '#') s++;
                result[i-1][j-1] = '0' + s;
            }
        }
    }
    return result;
}