#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long int LLI;

int baseline(int n, int t, const vector<int>& k_values) {
    int mx = -1;
    LLI sum = 0;
    int result = 0;
    for (int i = 0; i < n; ++i) {
        int k = k_values[i];
        mx = max(mx, k);
        sum += k;
        if (sum <= t) {
            result = 1 + ceil((double)(t + 0.5 - sum) / (double)mx);
        } else {
            result = 1;
        }
    }
    return result;
}

vector<int> generateInput(int n, int t) {
    vector<int> k_values(n);
    for (int i = 0; i < n; ++i) {
        k_values[i] = rand() % 1000000 + 1;
    }
    return k_values;
}