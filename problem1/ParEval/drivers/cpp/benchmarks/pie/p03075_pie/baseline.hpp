#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> generateInput() {
    vector<int> v(100000);
    for (int i = 0; i < 100000; ++i) {
        v[i] = i;
    }
    return v;
}

string baseline(const vector<int>& v, int k) {
    int a = v.size();
    int max = 0;

    for (int i = 0; i < a; ++i) {
        for (int j = i + 1; j < a; ++j) {
            if (v[j] - v[i] > max)
                max = v[j] - v[i];
        }
    }

    if (max > k)
        return ":(\n";
    else
        return "Yay!\n";
}