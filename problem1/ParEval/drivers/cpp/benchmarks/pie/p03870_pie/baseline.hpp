#pragma once

#include <vector>
#include <set>

int baseline(const std::vector<int>& a) {
    int n = a.size();
    int xor_sum = 0;
    for (int i = 0; i < n; i++)
        xor_sum ^= a[i];

    std::set<int> s;
    for (int i = 0; i < n; i++)
        s.insert(a[i] ^ (a[i] - 1));

    int ans = 0;
    for (int bit = 29; bit >= 0; bit--) {
        if (((1 << bit) & xor_sum) == 0) {
            continue;
        }
        int x = (1 << (bit + 1)) - 1;

        if (s.count(x)) {
            xor_sum ^= x;
            ans += 1;
        }
    }

    return xor_sum == 0 ? ans : -1;
}

std::vector<int> generateInput() {
    std::vector<int> input(1000000);
    for (int i = 0; i < 1000000; i++) {
        input[i] = i + 1;
    }
    return input;
}