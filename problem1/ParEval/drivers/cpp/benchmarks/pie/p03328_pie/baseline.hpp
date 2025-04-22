#pragma once

#include <vector>

using namespace std;

int baseline(int a, int b) {
    int d = b - a;
    int res = -1;
    for (int i = 1; i <= 999; i++) {
        for (int j = 1; j <= 999; j++) {
            int A = i * (i + 1) / 2;
            int B = j * (j + 1) / 2;
            if (A > a && B > b && B - A == d) {
                res = A - a;
                return res;
            }
        }
    }
    return res;
}

vector<int> generateInput() {
    return {1000000, 1000001};
}