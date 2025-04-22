#pragma once

#include <algorithm>
#include <vector>

int baseline(int n, int k, const std::vector<char>& s) {
    int count = 0;
    int i = 0;

    if (s[i] == 'R' && s[i + 1] == 'R') count++;
    for (i = 1; i < n - 1; i++) {
        if (s[i] == 'L' && s[i - 1] == 'L') count++;
        if (s[i] == 'R' && s[i + 1] == 'R') count++;
    }
    if (s[i] == 'L' && s[i - 1] == 'L') count++;

    int an = std::min((count + 2 * k), (n - 1));
    return an;
}

std::vector<char> generateInput(int n) {
    std::vector<char> s(n);
    for (int i = 0; i < n; i++) {
        s[i] = (i % 2 == 0) ? 'R' : 'L';
    }
    return s;
}