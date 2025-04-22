#pragma once

#include <vector>

using namespace std;

int baseline(int n) {
    int r = 0;

    for (int i = 1; i <= n; i++) {
        int c = 0;

        for (int j = 1; j <= i; j++) {
            if (i % j == 0) c++;
        }

        if (i % 2 == 1 && c == 8) r++;
    }

    return r;
}

vector<int> generateInput() {
    return {1000000}; // Example input to maximize the problem scale
}