#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int a, int b, int c) {
    return min(a * b, c);
}

vector<int> generateInput() {
    return {100000, 100000, 1000000000};
}