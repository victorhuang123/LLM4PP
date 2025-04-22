#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> generateInput() {
    vector<int> input = {1000000, 2000000, 1500000, 2500000};
    return input;
}

int baseline(int a, int b, int c, int d) {
    int ma = max(a, c);
    int mi = min(b, d);
    return max(0, mi - ma);
}