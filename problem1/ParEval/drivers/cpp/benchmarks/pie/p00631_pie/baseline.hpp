#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int baseline(int n, const vector<int>& a) {
    int mn, t, mask, s, u;

    t = 0;
    mn = INT_MAX;

    for(int i = 0; i < n; ++i){
        t += a[i];
    }

    mask = 1<<n;
    for(int i = 0; i < mask; i++){
        s = 0;
        for(int j = 0; j < n; j++){
            u = 1<<j;
            if(i&u) s += a[j];
        }  
        mn = min(mn, abs(s-(t-s)));
    }

    return mn;
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}