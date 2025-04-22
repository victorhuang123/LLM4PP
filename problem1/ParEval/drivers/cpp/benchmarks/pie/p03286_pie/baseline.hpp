#pragma once

#include<vector>
#include<cmath>

using namespace std;

vector<int> baseline(int n) {
    vector<int> s(3000, 0);
    int i = 0, k, t;

    if (n == 0) {
        return {0};
    }

    while (n != 0) {
        k = n % (-2);
        t = n / (-2);
        if (k < 0) {
            k = k - (-2);
            t++;
        }
        i++;
        n = t;
        s[i] = k;
    }

    vector<int> result;
    for (; i >= 1; i--) {
        result.push_back(s[i]);
    }

    return result;
}

vector<int> generateInput() {
    return {1000000}; // Example input to maximize the problem scale
}