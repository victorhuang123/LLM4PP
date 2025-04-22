#pragma once

#include <bits/stdc++.h>

using namespace std;

bool baseline(int n) {
    while (n) {
        if ((n % 10) == 9) {
            return true;
        }
        n /= 10;
    }
    return false;
}

int generateInput() {
    return 999999999; // Example input to maximize the problem scale
}