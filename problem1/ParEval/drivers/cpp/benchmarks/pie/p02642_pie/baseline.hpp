#pragma once

#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

#define rep(i,n) for(int i=0;i<(int)(n);++i)

int baseline(int N, const vi& A) {
    vi l(1000000+1, 0);
    vi c(1000000+1, 0);
    int mx = 0;

    rep(i, N) {
        int a = A[i];
        mx = max(mx, a);
        c[a]++;
    }

    for(int a : A) {
        for(int i = a * 2; i <= mx; i += a) l[i] = 1;
    }

    int ans = 0;
    for(int a : A) {
        if(!l[a] && c[a] <= 1) ans++;
    }
    return ans;
}

vi generateInput() {
    int N = 100000;
    vi A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = i + 1;
    }
    return A;
}