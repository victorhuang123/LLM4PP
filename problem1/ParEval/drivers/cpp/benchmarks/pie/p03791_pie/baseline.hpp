#pragma once

#include <vector>
#include <algorithm>
#define ll long long

ll baseline(const std::vector<int>& input) {
    int k = 0;
    ll ans = 1;
    for (int x : input) {
        ++k;
        if (x < (k << 1) - 1) {
            ans = (ans * k) % 1000000007;
            --k;
        }
    }
    while (k != 1) {
        ans = (ans * k) % 1000000007;
        --k;
    }
    return ans;
}