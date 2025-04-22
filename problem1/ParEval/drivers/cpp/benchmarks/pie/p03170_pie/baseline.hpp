#pragma once

#include<bits/stdc++.h>

#define mod 1000000007
#define MAX 1000005

using namespace std;

int baseline(int n, int k, vector<int>& arr) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = arr[i - 1];
    }
    vector<int> dp(k + 1, -1);
    function<int(int)> solve = [&](int k) {
        if (dp[k] != -1)
            return dp[k];
        if (k == 0)
            return dp[k] = 0;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] > k)
                continue;
            if (solve(k - a[i]) == 0) {
                ans = 1;
                break;
            }
        }
        return dp[k] = ans;
    };
    return solve(k);
}

