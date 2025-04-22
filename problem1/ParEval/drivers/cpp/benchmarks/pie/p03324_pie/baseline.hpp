#pragma once

#include <vector>
#include <iostream>

using namespace std;

long long baseline(long long d, long long n) {
    long long ans = 1;
    if (n == 100) {
        n++;
    }
    for (int i = 1; i <= d; i++) {
        ans *= 100;
    }
    return ans * n;
}

vector<long long> generateInput() {
    return {18, 100}; // Example input to maximize the problem scale
}