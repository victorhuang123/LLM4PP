#pragma once

#include<vector>
#include<algorithm>
#include<cstring>
#define Max int(2e5+10)

using namespace std;

int baseline(int n, vector<int>& p) {
    vector<int> a(n + 1), dp(n + 1, 0);
    vector<vector<int>> g(n + 1);

    for (int i = 1; i <= n; i++) {
        a[p[i]] = i;
    }
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i + 1]) {
            g[a[i]].push_back(a[i + 1]);
        }
    }

    function<int(int)> dfs = [&](int x) {
        if (dp[x] > 0) return dp[x];
        dp[x] = 1;
        for (int neighbor : g[x]) {
            dp[x] = max(dp[x], dfs(neighbor) + 1);
        }
        return dp[x];
    };

    int ma = -1;
    for (int i = 1; i <= n; i++) {
        ma = max(ma, dfs(i));
    }
    return n - ma;
}

vector<int> generateInput(int n) {
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }
    random_shuffle(p.begin() + 1, p.end());
    return p;
}