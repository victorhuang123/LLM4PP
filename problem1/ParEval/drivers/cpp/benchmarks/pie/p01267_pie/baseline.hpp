#pragma once

#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

using namespace std;

int baseline(int n, int a, int b, int c, int x, vector<int> &y) {
    vector<int> z(10000 * n + 1);
    z[0] = x;

    for (int i = 1; i <= 10000 * n; i++) {
        z[i] = (a * z[i - 1] + b) % c;
    }

    int head = 0;
    rep(t, 10000 + 1) {
        if (y[head] == z[t]) head++;
        if (head == n) return t;
    }

    return -1;
}

vector<int> generateInput(int n, int a, int b, int c, int x) {
    vector<int> y(n);
    vector<int> z(10000 * n + 1);
    z[0] = x;

    for (int i = 1; i <= 10000 * n; i++) {
        z[i] = (a * z[i - 1] + b) % c;
    }

    for (int i = 0; i < n; i++) {
        y[i] = z[i * 10000 / n];
    }

    return y;
}