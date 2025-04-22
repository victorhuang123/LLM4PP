#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<int> generate_input() {
    int n = 200000;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    return a;
}

vector<int> baseline(int n, const vector<int>& a) {
    vector<int> result;
    for (int i = n - 1; i >= 0; i -= 2) {
        result.push_back(a[i]);
    }
    for (int i = (n & 1); i < n; i += 2) {
        result.push_back(a[i]);
    }
    return result;
}