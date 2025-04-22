#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int n, int t, int a, const vector<int>& h) {
    int MIN;
    int x = INT_MAX;
    int z;
    a *= 1000;

    for(int i = 1; i <= n; i++) {
        MIN = t * 1000 - h[i] * 6;
        if(x > abs(MIN - a)) {
            x = abs(MIN - a);
            z = i;
        }
    }

    return z;
}

vector<int> generateInput(int n) {
    vector<int> h(n + 1);
    for(int i = 1; i <= n; i++) {
        h[i] = rand() % 1000000 + 1;
    }
    return h;
}