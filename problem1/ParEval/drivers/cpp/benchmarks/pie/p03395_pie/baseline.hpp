#pragma once

#include <vector>
#include <functional>
#include <cstring>

using namespace std;
using ll = long long;

ll baseline(int N, const vector<int>& a, const vector<int>& b) {
    int dp[60][60][60];
    memset(dp, -1, sizeof(dp));
    function<bool(int, int, int)> can = [&](int a, int b, int k) {
        int &res = dp[a][b][k];
        if (res != -1) {
            return res;
        }
        if (k == 0) {
            return res = (a == b);
        }
        return res = can(a, b, k - 1) || can(a % k, b, k - 1);
    };

    bool ok = true;
    for (int i = 0; i < N; i++) {
        ok &= can(a[i], b[i], 59);
    }
    if (!ok) {
        return -1;
    }

    vector<int> ks;
    auto solve = [&](int a, int b, int k) {
        vector<bool> dp(a + 1, false);
        dp[a] = true;
        for (int k : ks) {
            vector<bool> ndp = dp;
            for (int i = 0; i <= a; i++) {
                if (dp[i]) {
                    ndp[i % k] = true;
                }
            }
            dp = ndp;
        }
        for (int i = 0; i <= a; i++) {
            if (dp[i] && can(i, b, k - 1)) {
                return false;
            }
        }
        return true;
    };

    for (int k = 60; k >= 1; k--) {
        bool need = false;
        for (int i = 0; i < N; i++) {
            if (solve(a[i], b[i], k)) {
                need = true;
                break;
            }
        }
        if (need) {
            ks.push_back(k);
        }
    }

    ll ans = 0;
    for (int k : ks) {
        ans += 1ll << k;
    }
    return ans;
}

vector<int> generateInput(int N) {
    vector<int> a(N), b(N);
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 60;
        b[i] = rand() % 60;
    }
    return a, b;
}