#pragma once

#include<bits/stdc++.h>
using namespace std;

int baseline(int n, int k, vector<int>& p) {
    sort(p.begin(), p.end());
    int ret = 0;
    for (int i = 0; i < k; i++)
        ret += p[i];
    return ret;
}

vector<int> generateInput(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = rand() % 1000000 + 1;
    }
    return p;
}