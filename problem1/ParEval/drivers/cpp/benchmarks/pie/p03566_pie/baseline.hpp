#pragma once

#include <bits/stdc++.h>
using namespace std;

double baseline(int n, vector<int>& t, vector<int>& v) {
    int ans = 0;
    vector<int> tmp(2e6 + 5, 0);
    vector<int> miB(2e6 + 5, 0x3f3f3f3f), miF(2e6 + 5, 0x3f3f3f3f), mi(2e6 + 5, 0x3f3f3f3f);

    for (int i = 0; i < n; i++) t[i] *= 2, v[i] *= 2;
    for (int i = 1; i < n; i++) t[i] += t[i-1];
    for (int i = 1; i < n; i++) miB[t[i-1]] = v[i];
    miB[t[n-1]] = 0;
    for (int i = t[n-1]-1; ~i; i--) miB[i] = min(miB[i], miB[i+1]+1);
    for (int i = 0; i < n; i++) miF[t[i]] = v[i];
    miF[0] = 0;
    for (int i = 1; i <= t[n-1]; i++) miF[i] = min(miF[i], miF[i-1]+1);
    for (int i = 0; i < n; i++)
        for (int j = !i?0:t[i-1]; j <= t[i]; j++)
            mi[j] = min(mi[j], v[i]), tmp[j] = mi[j];
    for (int i = 0; i <= t[n-1]; i++) mi[i] = min(mi[i], min(miF[i],miB[i]));
    for (int i = 0; i < t[n-1]; i++) ans += (mi[i+1]+mi[i]);
    return (double)ans / 8.0;
}

vector<int> generateInput(int n) {
    vector<int> t(n), v(n);
    for (int i = 0; i < n; i++) {
        t[i] = rand() % 100000 + 1;
        v[i] = rand() % 100000 + 1;
    }
    return t, v;
}