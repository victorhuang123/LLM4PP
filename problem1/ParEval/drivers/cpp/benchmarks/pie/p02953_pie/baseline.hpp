#pragma once

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int maxx = 100005;

vector<int> generateInput() {
    vector<int> a(maxx);
    for (int i = 1; i <= maxx; ++i) {
        a[i] = i;
    }
    return a;
}

bool baseline(int n, vector<int>& a) {
    for(int i = 2; i <= n; i++) {
        if(a[i] > a[i-1]) {
            a[i] -= 1;
        }
    }
    for(int i = 2; i <= n; i++) {
        if(a[i] < a[i-1]) {
            return false;
        }
    }
    return true;
}