#pragma once

#include<bits/stdc++.h>

using namespace std;

#define int long long

vector<int> generateInput() {
    int n = 1e5;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
    a[n] = n - 1; // Introduce a duplicate to test the function
    return a;
}

bool baseline(int n, vector<int>& a) {
    sort(a.begin() + 1, a.end());
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i + 1]) {
            return false;
        }
    }
    return true;
}