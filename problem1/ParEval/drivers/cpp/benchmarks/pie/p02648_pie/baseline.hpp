#pragma once

#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

int baseline(int n, int Q, vector<int>& values, vector<int>& weights, vector<pii>& queries) {
    int D = 10;
    vector<int> dp(n + 1), val(n + 1), w(n + 1);
    vector<vector<pii>> can((1 << D) + 1);

    for (int i = 1; i <= n; i++) {
        val[i] = values[i-1];
        w[i] = weights[i-1];
    }
    dp[1] = 0;
    for (int i = 2; i <= n; i++) dp[i] = dp[i>>1] + 1;
    int m = min(n, (1<<D) - 1);
    can[0] = {{0, 0}};
    for (int i = 1; i <= m; i++) {
        auto &res = can[i];
        auto &from = can[i>>1];
        vector<pii> tmp = from;
        for (auto x : from) {
            tmp.emplace_back(x.first + w[i], x.second + val[i]);
        }
        sort(tmp.begin(), tmp.end());
        for (auto x : tmp) {
            if (!res.empty() && res.back().second >= x.second) continue;
            res.push_back(x);
        }
    }

    int max_ans = 0;
    for (auto &q : queries) {
        int v = q.first, L = q.second, ans = 0;
        function<void(int&, int, int, int)> query = [&](int &ans, int v, int L, int cur) {
            if (v <= m) {
                ans = max(ans, cur + (--lower_bound(can[v].begin(), can[v].end(), pii(L + 1, 0)))->second);
                return;
            }
            query(ans, v >> 1, L, cur);
            if (L >= w[v]) query(ans, v >> 1, L - w[v], cur + val[v]);
        };
        query(ans, v, L, 0);
        max_ans = max(max_ans, ans);
    }
    return max_ans;
}

vector<int> generateValues(int n) {
    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        values[i] = rand() % 100000 + 1;
    }
    return values;
}

vector<int> generateWeights(int n) {
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        weights[i] = rand() % 100000 + 1;
    }
    return weights;
}

vector<pii> generateQueries(int Q, int n) {
    vector<pii> queries(Q);
    for (int i = 0; i < Q; i++) {
        queries[i] = {rand() % n + 1, rand() % 100000 + 1};
    }
    return queries;
}