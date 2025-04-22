#pragma once

#include <vector>
#include <algorithm>

using namespace std;

bool baseline(int n, const vector<int>& a) {
    for (int i = 0; i < n; ++i) {
        if (((i + 1) ^ a[i]) & 1) {
            return false;
        }
    }
    for (int i = 0; i < n; ) {
        if (a[i] == i + 1) {
            ++i;
            continue;
        }
        int p;
        for (p = i; p < n - 2; p += 2) {
            if (a[p + 2] == p + 3 || a[p + 1] != p + 2) break;
        }
        int mx = 0, mn = n + 1;
        for (int j = i; j <= p; ++j) {
            mx = max(mx, a[j]);
            mn = min(mn, a[j]);
        }
        if (mx != p + 1 || mn != i + 1) {
            return false;
        }
        int f1 = 0, f2 = 0;
        for (int j = i; j <= p; j += 2) {
            if (a[j] > f1) {
                f2 = f1;
                f1 = a[j];
            } else if (a[j] > f2) {
                f2 = a[j];
            } else {
                return false;
            }
        }
        i = p + 1;
    }
    return true;
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    return a;
}