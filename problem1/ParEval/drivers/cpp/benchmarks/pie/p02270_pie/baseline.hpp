#pragma once

#include <vector>
#include <algorithm>

using namespace std;

typedef long long llong;

int baseline(int n, int k, const vector<llong>& w) {
    auto check = [&](llong P) {
        int i = 0;
        for (int j = 0; j < k; j++) {
            llong s = 0;
            while (i < n && s + w[i] <= P) {
                s += w[i];
                i++;
            }
        }
        return i;
    };

    llong left = 0;
    llong right = n * *max_element(w.begin(), w.end());
    while (right - left > 1) {
        llong mid = (left + right) / 2;
        int v = check(mid);
        if (v >= n) right = mid;
        else left = mid;
    }

    return right;
}

vector<llong> generateInput(int n) {
    vector<llong> w(n, 10000);
    return w;
}