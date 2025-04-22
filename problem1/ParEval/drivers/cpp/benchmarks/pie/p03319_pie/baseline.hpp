#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int n, int K) {
    return (n - 2) / (K - 1) + 1;
}

vector<int> generateInput() {
    return {1000000000, 2};
}