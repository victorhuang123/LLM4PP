#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> generateInput(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}

int baseline(const vector<int>& a) {
    int sum = 0;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sum += a[i] * a[j];
        }
    }
    return sum;
}