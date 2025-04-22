#pragma once

#include<bits/stdc++.h>

using namespace std;

#define INS(x) x.begin(),x.end()

int baseline(int n, const vector<int>& a) {
    int ans = 0;
    for (int i = 0; i < n - 2; i++) {
        vector<int> b = {a[i], a[i + 1], a[i + 2]};
        sort(INS(b));
        if (a[i] != a[i + 1] && a[i + 1] != a[i + 2] && a[i + 1] == b[1]) ans++;
    }
    return ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}