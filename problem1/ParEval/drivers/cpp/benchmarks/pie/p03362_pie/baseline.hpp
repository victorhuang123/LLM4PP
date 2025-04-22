#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> generateInput() {
    return {10000}; // Example input to maximize the problem scale
}

vector<int> baseline(int N) {
    vector<int> v;
    for (int i = 11; i <= 55555; i += 5) {
        int no = 0;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                no++;
                break;
            }
        }
        if (!no) v.emplace_back(i);
    }
    vector<int> result(v.begin(), v.begin() + N);
    return result;
}