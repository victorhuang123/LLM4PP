#pragma once

#include<bits/stdc++.h>

#define N 100005

#define int long long

using namespace std;

vector<int> generateInput(int n, int m, long long k) {
    vector<int> x(n + 1), a(m + 1);
    for (int i = 1; i <= n; i++) x[i] = i;
    for (int i = 1; i <= m; i++) a[i] = i % (n - 1) + 1;
    return {n, m, k, x, a};
}

vector<long long> baseline(int n, int m, long long k, vector<int>& x, vector<int>& a) {
    int p[N], s[N], cnt = 0;
    int be[N], num[N], v[N];
    vector<int> q[N];

    auto dfs = [&](int x, int dep, auto&& dfs) -> void {
        num[x] = dep; v[x] = 1; be[x] = cnt;
        q[cnt].push_back(x);
        if (!v[p[x]]) dfs(p[x], dep + 1, dfs);
    };

    memset(v, 0, sizeof(v));
    for (int i = 1; i < n; i++) s[i] = x[i + 1] - x[i];
    for (int i = 1; i < n; i++) p[i] = i;
    for (int i = 1; i <= m; i++) { swap(p[a[i]], p[a[i] - 1]); }
    for (int i = 1; i < n; i++) if (!v[i]) cnt++, dfs(i, 0, dfs);

    vector<long long> result;
    result.push_back(x[1]);
    long long now = x[1];
    for (int i = 1; i < n; i++) {
        now += s[q[be[i]][(num[i] + k) % q[be[i]].size()]];
        result.push_back(now);
    }
    return result;
}