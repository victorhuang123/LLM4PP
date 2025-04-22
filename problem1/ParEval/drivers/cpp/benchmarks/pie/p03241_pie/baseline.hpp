#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int n, int m) {
    set<int> s;
    for(int i = 1; i <= sqrt(m+1); ++i){
        if(m%i == 0){
            s.insert(m/i);
            s.insert(i);
        }
    }
    int x = *(s.lower_bound(n));
    return m/x;
}

vector<int> generateInput() {
    int n = 1e5;
    int m = 1e9;
    return {n, m};
}