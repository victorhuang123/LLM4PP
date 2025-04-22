#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

long long baseline(int x) {
    x /= 5;
    return (x / 100) * 1000 + (x % 100) * 5;
}

vector<int> generate_input() {
    vector<int> input(1000000, 1000000000);
    return input;
}