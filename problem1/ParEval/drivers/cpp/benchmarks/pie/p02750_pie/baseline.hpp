#pragma once

#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

struct node {
    LL a, b;
};

bool cmp(node x, node y) {
    if (x.a == 0 && y.a == 0) return x.b < y.b;
    return y.a * (x.b + 1) < x.a * (y.b + 1);
}

LL baseline(LL n, LL T, vector<node>& s) {
    LL st, ans = 0;
    st = n + 1;
    sort(s.begin() + 1, s.begin() + 1 + n, cmp);

    for (LL i = n; i >= 1; i--) if (s[i].a == 0) st = i;

    vector<vector<LL>> dp(n + 1, vector<LL>(32, T + 1));
    dp[0][0] = 0;

    for (LL i = 1; i < st; i++) {
        dp[i][0] = dp[i - 1][0];
        for (LL j = 1; j <= 31; j++) {
            dp[i][j] = min(dp[i - 1][j], (1 + dp[i - 1][j - 1]) * (1 + s[i].a) + s[i].b);
            dp[i][j] = min(dp[i][j], T + 1);
        }
    }

    for (LL j = 0; j <= 31; j++) {
        LL tt = dp[st - 1][j];
        if (tt > T) continue;
        ans = max(ans, j);
        for (LL k = st; k <= n; k++) {
            if (tt + s[k].b + 1 > T) break;
            ans = max(ans, (k - st + j + 1));
            tt += (s[k].b + 1);
        }
    }

    return ans;
}

vector<node> generateInput(LL n, LL T) {
    vector<node> s(n + 1);
    for (LL i = 1; i <= n; i++) {
        s[i].a = rand() % 100000;
        s[i].b = rand() % 100000;
    }
    return s;
}