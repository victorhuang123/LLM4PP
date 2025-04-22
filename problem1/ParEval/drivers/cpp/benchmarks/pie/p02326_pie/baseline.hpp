#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ALL(a)  a.begin(),a.end()
#define SZ(a) int((a).size())
#define SORT(c) sort(ALL((c)))
#define UNIQ(c) (c).erase(unique(ALL((c))), end((c)))
#define FOR(i, s, e) for (int(i) = (s); (i) < (e); (i)++)
#define debug(x) cerr << #x << ": " << x << endl

using LL = long long; template<class T> using V = vector<T>;

LL baseline(int H, int W, V<V<int>>& a) {
    V<V<int>> dp(H + 1, V<int>(W + 1, 0));
    LL ans = 0;

    FOR(i, 1, H + 1) {
        FOR(j, 1, W + 1) {
            if (a[i][j] == 1) dp[i][j] = 0;
            else dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
        }
    }

    FOR(i, 1, H + 1) {
        FOR(j, 1, W + 1) {
            ans = max(ans, (LL)dp[i][j]);
        }
    }

    return ans * ans;
}

V<V<int>> generateInput(int H, int W) {
    return V<V<int>>(H + 1, V<int>(W + 1, 0));
}