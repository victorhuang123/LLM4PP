#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int n, const vector<int>& b) {
    int result = b[0];
    for (int i = 1; i < n - 1; i++) {
        result += min(b[i - 1], b[i]);
    }
    result += b[n - 2];
    return result;
}

vector<int> generateInput(int n) {
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = i + 1;
    }
    return b;
}