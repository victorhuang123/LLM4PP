#pragma once

#include <bits/stdc++.h>

#define fr first
#define sc second
#define mk make_pair
#define pb push_back
#define pf push_front
#define pii pair <int ,int>
#define all(s) s.begin (), s.end ()
#define int long long

using namespace std;

const int N = 1e5 + 5, mod = 1e9 + 7;

int baseline(int n, int a, int b, vector<int>& ar) {
    if (a > b) swap(a, b);

    int dp[2][N], l = 1, L[N];
    dp[0][1] = dp[1][1] = 1;

    L[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (ar[i] - ar[i - 1] >= a)
            L[i] = L[i - 1];
        else
            L[i] = i;
    }
    ar[0] = -1e18;

    for (int i = 2; i <= n; i++) {
        if (ar[i] - ar[i - 1] >= a)
            dp[0][i] = (dp[0][i - 1] + dp[1][i - 1]) % mod;
        else if (ar[i] - ar[i - 2] >= a)
            dp[0][i] = dp[1][i - 1];
        else if (i > 2) {
            return 0;
        }

        while (ar[i] - ar[l] >= b) l++;

        if (l == i)
            dp[1][i] = (dp[0][i - 1] + dp[1][i - 1]) % mod;
        else if (L[i - 1] <= l)
            dp[1][i] = dp[0][l];
    }
    return (dp[1][n] + dp[0][n]) % mod;
}

vector<int> generateInput(int n) {
    vector<int> ar(n + 1);
    ar[1] = 1;
    for (int i = 2; i <= n; i++) {
        ar[i] = ar[i - 1] + 1;
    }
    return ar;
}