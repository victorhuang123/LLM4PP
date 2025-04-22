#pragma once

#include <bits/stdc++.h>

using namespace std;

using i32 = std::int_fast32_t;
using i64 = std::int_fast64_t;

#define REP(i, stop) FOR(i, 0, stop)
#define FOR(i, start, stop) for (int i = start, i##_len = stop; i < i##_len; ++i)
#define RREP(i, n) for (int i = n; i-- > 0;)

const i32 M = 998244353;

i32 baseline(const vector<i32>& a) {
    i32 n = a.size();
    i32 sum = 0;
    i32 ans = 1;
    vector<i32> dp(90310, 0);
    vector<i32> dq(90310, 0);
    dp[0] = 1;
    dq[0] = 1;
    REP(i, n) {
        RREP(t, sum + 1) {
            (dp[t + a[i]] += dp[t]) %= M;
            (dp[t] *= 2) %= M;
            (dq[t + a[i]] += dq[t]) %= M;
        }
        sum += a[i];
        ans = (ans * 3) % M;
    }
    i32 lim = (sum - 1) / 2;
    FOR(t, lim + 1, sum + 1) {
        ans = (ans - dp[t] * 3) % M;
    }
    if (sum % 2 == 0) {
        ans = (ans + dq[sum / 2] * 3) % M;
    }
    ans = (ans + M) % M;
    return ans;
}

vector<i32> generateInput(i32 n) {
    vector<i32> a(n, 1);
    return a;
}