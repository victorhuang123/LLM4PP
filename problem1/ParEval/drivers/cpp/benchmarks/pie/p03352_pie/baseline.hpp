#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int baseline(int X) {
    int ans = 1;

    for (int b = 1; b <= 1000; b++) {
        for (int p = 2; p <= 10; p++) {
            if ((pow(b, p) <= X) && (pow(b, p) >= ans)) {
                ans = pow(b, p);
            }
        }
    }

    return ans;
}

vector<int> generateInput() {
    vector<int> input;
    for (int i = 1; i <= 1000000; i++) {
        input.push_back(i);
    }
    return input;
}