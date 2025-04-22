#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long

ll baseline(int n, int m, vector<ll>& arr) {
    vector<vector<vector<ll>>> mem(n, vector<vector<ll>>(n, vector<ll>(m + 1, -1)));
    function<ll(int, int, int)> solve = [&](int l, int r, int steps) {
        if(steps < 0)
            return -inf;
        if(steps == 0 || l > r)
            return 0;
        ll& ret = mem[l][r][steps];
        if(~ret)
            return ret;
        ret = -inf;
        ll c1 = solve(l + 1, r, steps - 1) + arr[l];
        ll c2 = solve(l, r - 1, steps - 1) + arr[r];
        ll c3 = solve(l + 1, r, steps - 2);
        ll c4 = solve(l, r - 1, steps - 2);
        ret = max(max(c1, c2), max(c3, c4));
        return ret;
    };
    ll best = -inf;
    for (int i = 0; i <= m; ++i) {
        best = max(best, solve(0, n - 1, i));
    }
    return best;
}

vector<ll> generateInput(int n) {
    vector<ll> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}