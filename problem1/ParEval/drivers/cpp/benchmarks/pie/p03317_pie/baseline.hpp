#pragma once

#include <bits/stdc++.h>

using namespace std;

long long baseline(double n, double k, vector<int>& input) {
    double pos = 0; k--;
    for(int i = 0; i < n; i++) {
        if(input[i] == 1) pos = i;
    }
    long long tmp1, tmp2;
    int p = pos, kk = k;
    while(p % kk && p + 1 < n) p++;
    pos = p; tmp1 = ceil(pos / k);
    tmp2 = ceil((n - pos - 1) / k);
    long long res = tmp1 + tmp2;
    return res;
}

vector<int> generateInput(double n) {
    vector<int> input(n, 0);
    input[n / 2] = 1;
    return input;
}