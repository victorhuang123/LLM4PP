#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<int> generateInput() {
    // Maximizing the problem scale with large values
    int n = 1e6;
    int k = 1e6;
    int x = 1e6;
    return {n, k, x};
}

int baseline(int n, int k, int x) {
    return ((n + k) * x) / 2;
}