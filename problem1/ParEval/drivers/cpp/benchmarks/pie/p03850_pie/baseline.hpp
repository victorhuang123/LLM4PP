#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N=1e5+100;

LL baseline(int n, vector<int>& a, vector<char>& op) {
    vector<vector<LL>> f(N, vector<LL>(3, -1e18));
    f[1][0] = a[1];

    for(int i = 1; i < n; ++i) {
        if(op[i] == '-') f[i+1][1] = max(f[i+1][1], f[i][0] - a[i+1]);
        if(op[i] == '+') f[i+1][0] = max(f[i+1][0], f[i][0] + a[i+1]);
        if(op[i] == '-') f[i+1][0] = max(f[i+1][0], f[i][0] - a[i+1]);

        if(op[i] == '+') f[i+1][1] = max(f[i+1][1], f[i][1] - a[i+1]);
        if(op[i] == '-') f[i+1][1] = max(f[i+1][1], f[i][1] + a[i+1]);
        if(op[i] == '-') f[i+1][2] = max(f[i+1][2], f[i][1] + a[i+1]);
        if(op[i] == '+') f[i+1][0] = max(f[i+1][0], f[i][1] + a[i+1]);
        if(op[i] == '-') f[i+1][0] = max(f[i+1][0], f[i][1] - a[i+1]);

        if(op[i] == '+') f[i+1][2] = max(f[i+1][2], f[i][2] + a[i+1]);
        if(op[i] == '-') f[i+1][2] = max(f[i+1][2], f[i][2] + a[i+1]);
        if(op[i] == '+') f[i+1][0] = max(f[i+1][0], f[i][2] + a[i+1]);
        if(op[i] == '-') f[i+1][0] = max(f[i+1][0], f[i][2] - a[i+1]);
        if(op[i] == '-') f[i+1][1] = max(f[i+1][1], f[i][2] - a[i+1]);
    }

    return max({f[n][0], f[n][1], f[n][2]});
}

vector<int> generateInputA(int n) {
    vector<int> a(n);
    for(int i = 0; i < n; ++i) a[i] = rand() % 1000000 + 1;
    return a;
}

vector<char> generateInputOp(int n) {
    vector<char> op(n);
    for(int i = 0; i < n; ++i) op[i] = (rand() % 2) ? '+' : '-';
    return op;
}