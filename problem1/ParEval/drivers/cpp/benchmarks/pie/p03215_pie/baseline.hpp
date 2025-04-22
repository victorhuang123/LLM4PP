#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define LL long long

LL baseline(int n, int m, const vector<int>& a) {
    vector<LL> q;

    for (int i = 1; i <= n; i++) {
        LL d = 0;
        for (int j = i; j <= n; j++) {
            d += a[j];
            q.push_back(d);
        }
    }

    LL s = 0;
    for (int i = 40; i >= 0; i--) {
        LL d = s | (LL)pow(2, i);
        int k = 0;
        for (int j = 0; j < n * (n + 1) / 2; j++) {
            if ((q[j] & d) == d) {
                k++;
            }
        }
        if (k >= m) {
            s += (LL)pow(2, i);
        }
    }

    return s;
}

vector<int> generateInput(int n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
    return a;
}