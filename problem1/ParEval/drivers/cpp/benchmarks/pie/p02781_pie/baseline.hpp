#pragma once

#include <bits/stdc++.h>

using namespace std;

#define rep(i,j,k) for(int i = (int)(j);i <= (int)(k);i ++)

const int maxn=(int)1e6+5;

long long dp[105][105][105];

long long f(int l, int st, int flag, int L, int k, string n) {
    if(st > k) return 0;
    if(l >= L) return st == k;
    if(dp[l][st][flag] != -1) return dp[l][st][flag];

    int upper = flag ? n[l] - '0' : 9;
    long long ans = 0;
    rep(i, 0, upper) ans += f(l + 1, st + (i != 0), flag && (i == upper), L, k, n);

    return dp[l][st][flag] = ans;
}

long long baseline(string n, int k) {
    int L = n.length();
    memset(dp, -1, sizeof(dp));
    return f(0, 0, 1, L, k, n);
}

string generateInput() {
    return "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
}