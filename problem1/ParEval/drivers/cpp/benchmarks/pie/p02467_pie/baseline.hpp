#pragma once

#include<bits/stdc++.h>
using namespace std;

string baseline(long long x) {
    stringstream result;
    for (long long i = 2; i <= 1000000; i++) {
        if (x == 1) {
            break;
        }
        while (x % i == 0) {
            result << " " << i;
            x = x / i;
        }
    }
    if (x > 1) {
        result << " " << x;
    }
    return result.str();
}