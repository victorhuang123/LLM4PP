#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> generateInput() {
    return {1000000}; // Example input to maximize problem scale
}

ll baseline(int n) {
    long long ans = 1, fac = 0;
    vector<int> pl;

    pl.push_back(2);

    for(int i = 3; i <= n; i += 2) {
        int k = 0;
        for(int j = 3; j <= sqrt(i); j += 2) {
            if(i % j == 0) {
                k = 1;
                break;
            }
        }
        if(k == 0) pl.push_back(i);
    }

    for(int i = 0; i < pl.size(); i++) {
        int j = pl[i];
        for(; j <= n; j *= pl[i]) {
            fac += n / j;
        }
        ans *= fac + 1;
        ans %= 1000000007;
        fac = 0;
    }

    return ans;
}