#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<int> generateInput(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % n;
    }
    return a;
}

int baseline(int n, const vector<int>& a) {
    vector<int> x(n, -1);
    vector<int> y(n, -1);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int p = i, c = 0;
        while (x[p] == -1) {
            x[p] = c++;
            y[p] = i;
            p = (p + a[p]) % n;
        }
        if (y[p] == i) ans += (c - x[p]);
    }

    return ans;
}