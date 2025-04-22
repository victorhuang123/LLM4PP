#pragma once

#include <vector>
#include <string>
#include <algorithm>

int baseline(const std::string& x) {
    int a = 0, b = 0, c = 0, d = 0, maxi = 0;
    int leng = x.length();

    while (1) {
        if (a == leng) break;
        if (x[a] != 'J') {
            a++;
        } else {
            while (1) {
                if (x[a] == 'J') {
                    b++;
                    a++;
                } else {
                    break;
                }
            }
            while (1) {
                if (x[a] == 'O') {
                    c++;
                    a++;
                } else {
                    break;
                }
            }
            while (1) {
                if (x[a] == 'I') {
                    d++;
                    a++;
                } else {
                    break;
                }
            }
            if (b >= c && c <= d) {
                maxi = std::max(maxi, c);
            }
            b = 0;
            c = 0;
            d = 0;
        }
    }
    return maxi;
}

std::string generateInput() {
    return std::string(1000000, 'J') + std::string(1000000, 'O') + std::string(1000000, 'I');
}