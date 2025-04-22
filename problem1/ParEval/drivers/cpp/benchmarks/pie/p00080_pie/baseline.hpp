#pragma once

#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

bool eq(double x, double y) {
    return abs(x - y) < 0.00001 * y;
}

double baseline(long long q) {
    vector<double> x(100);
    x[1] = q / 2.0;
    for (int i = 2; ; i++) {
        x[i] = x[i - 1] - (x[i - 1] * x[i - 1] * x[i - 1] - (double)q) / (3 * x[i - 1] * x[i - 1]);
        if (eq(x[i] * x[i] * x[i], (double)q)) {
            return x[i];
        }
    }
}

vector<long long> generateInput() {
    return {999999999999999999LL};
}