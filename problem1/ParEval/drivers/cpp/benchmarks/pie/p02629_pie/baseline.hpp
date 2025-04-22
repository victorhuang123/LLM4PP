#pragma once

#include <vector>
#include <string>
#include <algorithm>

std::string baseline(long long a) {
    std::vector<long long> f(81, 0);
    f[1] = 1;
    f[2] = 26;
    for (int i = 3; i <= 80; ++i) {
        f[i] = f[i-1] * 26;
    }
    for (int i = 2; i <= 80; ++i) {
        f[i] += f[i-1];
    }
    
    int b = 0;
    for (int i = 1; i <= 50; ++i) {
        if (a < f[i]) {
            a -= f[i-1];
            b = i-1;
            break;
        }
    }
    
    std::string s;
    for (int i = 1; i <= b; ++i) {
        s.push_back(a % 26 + 'a');
        a /= 26;
    }
    std::reverse(s.begin(), s.end());
    return s;
}

std::vector<long long> generateInput() {
    std::vector<long long> inputs;
    for (long long i = 1; i <= 1000000000000000LL; i *= 10) {
        inputs.push_back(i);
    }
    return inputs;
}