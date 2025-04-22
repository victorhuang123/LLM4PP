#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int n, int x, vector<int>& v) {
    int s = 0;

    for(int &d : v) {
        s += d;
    }

    sort(v.begin(), v.end());

    x -= s;

    return (n + (x / v[0]));
}

vector<int> generateInput(int n) {
    vector<int> v(n);
    for(int i = 0; i < n; ++i) {
        v[i] = 1 + rand() % 1000000;
    }
    return v;
}