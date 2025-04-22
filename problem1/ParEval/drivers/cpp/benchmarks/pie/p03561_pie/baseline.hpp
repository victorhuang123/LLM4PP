#pragma once

#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; i++)

vector<int> baseline(int k, int n) {
    vector<int> result;
    if(k % 2 == 0) {
        rep(i, n) result.push_back(k / (1 + !i));
        return result;
    }

    vector<int> v(n, k + 1 >> 1);
    int j = n;
    rep(i, n - i - 1) if(--v[--j]) while(++j < n) v[j] = k;
    rep(i, j) result.push_back(v[i]);
    return result;
}

vector<int> generateInput() {
    int k = 1000000;
    int n = 1000000;
    return {k, n};
}