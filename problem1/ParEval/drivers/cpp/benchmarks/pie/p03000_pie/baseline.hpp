#pragma once

#include <bits/stdc++.h>

using namespace std;

const int INF = numeric_limits<int>::max();
const int MAXN = 3e5 + 1;
const int MOD = 1e9 + 7;
const double res = 1e-9;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int baseline(int n, int x, const vector<int>& k_values) {
    int now = 0, ans = 1;
    for (int k : k_values) {
        now += k;
        ans += now <= x;
    }
    return ans;
}

vector<int> generate_input(int n) {
    vector<int> k_values(n);
    for (int i = 0; i < n; ++i) {
        k_values[i] = rnd() % 1000000 + 1;
    }
    return k_values;
}