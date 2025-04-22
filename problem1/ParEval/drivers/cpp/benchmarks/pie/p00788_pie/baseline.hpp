#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

double mysqrt(double x) {
    double l = 0, r = x;
    for (int i = 0; i < 64; i++) {
        double m = (l + r) / 2.0;
        if (m * m < x) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

vector<int> baseline(int p, int n) {
    double sp = mysqrt(p);
    int a1 = 0, b1 = 1, a2 = p, b2 = 1;

    for (int i = 1; i <= n; i++) {
        int l = 0, r = n;

        for (int x = 0; x < 50; x++) {
            int m = (l + r + 1) / 2;
            if ((double)m / i < sp) {
                if (__gcd(m, i) == 1) {
                    if (m * b1 > a1 * i) {
                        a1 = m;
                        b1 = i;
                    }
                }
                l = m;
            } else {
                r = m - 1;
            }
        }

        l = 0, r = n;
        for (int x = 0; x < 50; x++) {
            int m = (l + r) / 2;
            if ((double)m / i > sp) {
                if (__gcd(m, i) == 1) {
                    if (m * b2 < a2 * i) {
                        a2 = m;
                        b2 = i;
                    }
                }
                r = m;
            } else {
                l = m + 1;
            }
        }
    }

    return {a2, b2, a1, b1};
}

vector<int> generate_input() {
    return {1000000, 1000000};
}