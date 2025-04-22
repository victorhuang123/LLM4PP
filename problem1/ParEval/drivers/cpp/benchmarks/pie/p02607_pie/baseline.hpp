#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int n, vector<int>& a) {
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(i & 1 && a[i] & 1)
            ans++;
    }
    return ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        a[i] = i;
    }
    return a;
}