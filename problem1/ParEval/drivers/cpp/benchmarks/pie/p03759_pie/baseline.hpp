#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> generateInput() {
    return {1000000, 1000002, 1000004};
}

bool baseline(int a, int b, int c) {
    return (b - a) == (c - b);
}