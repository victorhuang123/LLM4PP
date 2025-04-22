#pragma once

#include<bits/stdc++.h>

using namespace std;

#define LL long long

vector<LL> generateInput(int n) {
    vector<LL> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % 1000000 + 1;
        b[i] = rand() % 1000000 + 1;
    }
    return a, b;
}

double baseline(int n, vector<LL>& a, vector<LL>& b) {
    vector<LL> tmp(n);
    int Mx = 0, t = 0;
    for (int i = 1; i <= n; ++i) if (a[i] >= a[Mx]) Mx = i;
    for (int i = Mx; i <= n; ++i) tmp[++t] = a[i];
    for (int i = 1; i < Mx; ++i) tmp[++t] = a[i];
    for (int i = 1; i <= n; ++i) a[i] = tmp[i];
    t = 0;
    for (int i = Mx; i <= n; ++i) tmp[++t] = b[i];
    for (int i = 1; i < Mx; ++i) tmp[++t] = b[i];
    for (int i = 1; i <= n; ++i) b[i] = tmp[i];
    a.push_back(a[1]);
    vector<LL> c(n + 1);
    for (int i = 2; i <= n; ++i) c[i] = 2 * c[i - 1] - c[i - 2] + 2 * b[i - 1], a[i] -= c[i];
    vector<int> S(n + 1);
    int T = 0;
    for (int i = 1; i <= n; ++i) {
        while (T > 1 && ((a[S[T]] - a[S[T - 1]]) * (i - S[T]) - (a[i] - a[S[T]]) * (S[T] - S[T - 1])) > 0) --T;
        S[++T] = i;
    }
    LL ans = a[S[1]] + a[S[T]];
    for (int i = 2; i <= T; ++i) ans += (a[S[i]] + a[S[i - 1]]) * (S[i] - S[i - 1]);
    for (int i = 1; i <= n; ++i) ans += 2 * c[i];
    return 0.5 * (ans - 2 * a[1]) / (n - 1);
}