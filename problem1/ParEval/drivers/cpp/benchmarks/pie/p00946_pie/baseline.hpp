#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<int> baseline(int n, int m, vector<int>& a) {
    vector<bool> b1(n + 1, true);
    vector<bool> b2(n + 1, true);
    vector<int> result;

    for (int i = 0; i < m; i++) {
        b1[a[i]] = false;
    }

    for (int i = m - 1; i >= 0; i--) {
        if (b2[a[i]]) {
            result.push_back(a[i]);
            b2[a[i]] = false;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (b1[i]) {
            result.push_back(i);
        }
    }

    return result;
}

vector<int> generateInput(int n, int m) {
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        a[i] = rand() % n + 1;
    }
    return a;
}