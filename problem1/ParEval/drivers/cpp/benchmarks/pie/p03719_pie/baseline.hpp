#pragma once

#include <vector>
#include <string>

std::string baseline(int n, int m, int k) {
    if(n <= k && m >= k)
        return "Yes";
    else
        return "No";
}

std::vector<int> generateInput() {
    return {1000000000, 1000000000, 1000000000};
}