#pragma once

#include <vector>
#include <algorithm>

int baseline(int a, int b, int c, int x, int y) {
    int cost, ans;
    ans = a * x + b * y;
    for (int i = 0; i <= 100000; i++) {
        cost = c * i * 2 + a * std::max(0, x - i) + b * std::max(0, y - i);
        ans = std::min(ans, cost);
    }
    return ans;
}