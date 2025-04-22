#pragma once

#include <bits/stdc++.h>
using namespace std;

vector<int> generateInput() {
    int n = 100000;
    vector<int> ar(n);
    for (int i = 0; i < n; i++) {
        ar[i] = rand() % 100000;
    }
    return ar;
}

int baseline(const vector<int>& ar) {
    vector<int> cc(100050, 0);
    for (int i = 0; i < ar.size(); i++) {
        cc[ar[i]]++;
    }
    long long h = 0, l = 0;
    for (int i = 0; i < 100050; i++) {
        if (cc[i] != 0) {
            if (cc[i] % 2 == 0)
                h++;
            else
                l++;
        }
    }
    if (h % 2 == 0)
        return l + h;
    else
        return l + h - 1;
}