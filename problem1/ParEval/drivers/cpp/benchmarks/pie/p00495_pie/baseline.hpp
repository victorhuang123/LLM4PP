#pragma once

#include <vector>

using namespace std;

int baseline(int A, int B, const vector<int>& P, const vector<int>& Q) {
    int l = 1;
    int r = B;
    int m;

    while(r - l > 1) {
        m = (l + r) / 2;

        bool ok = false;

        for (int j = 0; j < (B - m); j++) {
            int ptr = j;

            for (int k = 0; k < A; k++) {
                if (P[k] == Q[ptr]) {
                    ptr++;
                }

                if (ptr == j + m) {
                    break;
                }
            }

            if (ptr == j + m) {
                ok = true;
            }
        }

        if (ok) {
            l = m;
        } else {
            r = m;
        }
    }

    return l;
}

vector<int> generateInput(int size) {
    vector<int> input(size);
    for (int i = 0; i < size; ++i) {
        input[i] = i % 100; // Example pattern to maximize problem scale
    }
    return input;
}