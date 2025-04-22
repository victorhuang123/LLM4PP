#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int a, int b, int c, int d) {
    int count1 = 0;
    while (a > 0 && c > 0) {
        if (count1 % 2) {
            a -= d;
            if (a <= 0) {
                return 0;
            }
        } else {
            c -= b;
            if (c <= 0) {
                return 1;
            }
        }
        count1++;
    }
    return -1;
}

vector<int> generateInput() {
    return {1000000, 1, 1000000, 1};
}