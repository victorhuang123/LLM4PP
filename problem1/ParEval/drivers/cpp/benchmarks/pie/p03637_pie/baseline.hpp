#pragma once

#include<bits/stdc++.h>

using namespace std;

#define LL long long

string baseline(LL n, vector<LL>& a) {
    LL M4 = 0, M2 = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] % 4 == 0)
            M4++;
        else if(a[i] % 2 == 0)
            M2++;
    }
    M2 = M2 / 2 * 2;
    if(M4 * 2 + 1 + M2 >= n)
        return "Yes";
    else
        return "No";
}

vector<LL> generateInput(LL n) {
    vector<LL> a(n);
    for(LL i = 0; i < n; i++) {
        a[i] = 2 * (i + 1);
    }
    return a;
}