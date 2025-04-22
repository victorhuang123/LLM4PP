#pragma once

#include <vector>
using namespace std;

int baseline(int n, int m, const vector<int>& input) {
    if (n == 0 || m == 0) {
        return 0;
    }

    int now = 0;
    for (int i = 0; i < m; i++) {
        now += input[i];
    }

    int max_sum = now;
    for (int i = m; i < n; i++) {
        now -= input[i - m];
        now += input[i];

        if (now > max_sum) {
            max_sum = now;
        }
    }

    return max_sum;
}

vector<int> generateInput(int n) {
    vector<int> input(n);
    for (int i = 0; i < n; i++) {
        input[i] = i + 1;
    }
    return input;
}