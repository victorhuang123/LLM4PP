#pragma once

#include<bits/stdc++.h>
using namespace std;

int baseline(int n, vector<int>& a) {
    int ans = INT_MAX;
    for(int i = -100; i <= 100; i++) {
        int cost = 0;
        for(int j = 0; j < n; j++) {
            cost += (i - a[j]) * (i - a[j]);
        }
        ans = min(ans, cost);
    }
    return ans;
}

