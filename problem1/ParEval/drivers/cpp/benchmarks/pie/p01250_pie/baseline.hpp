#pragma once

#include <utility>
#include <vector>
#include <cmath>

using namespace std;

pair<int, int> baseline(double r) {
    pair<int, int> a(9999999, 999999);
    double pi = M_PI;

    for (int i = 1; i < 100000; i++) {
        for (int k = -1; k < 2; k += 2) {
            for (int j = 0; j < 2; j++) {
                int nu = (int)((pi + r * k) * i) + j;
                if (abs(nu - pi * i) <= r * i) {
                    a = min(a, make_pair(i, nu));
                }
            }
        }
    }
    return a;
}

vector<double> generateInput() {
    return {0.0001};
}