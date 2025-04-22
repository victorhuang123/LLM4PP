#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int baseline(int n, int k, const vector<char>& s, const vector<char>& t) {
    vector<int> sum(n + 1, 0);
    vector<int> dp(n + 1, 0);
    struct Queue {
        vector<pii> a;
        int s, t;

        void init(int size) {
            a.resize(size);
            s = 1; t = 0;
        }

        void update(int pos, int val) {
            while (s <= t && val < a[t].second) t--;
            a[++t] = make_pair(pos, val);
            while (s <= t && a[t].first - a[s].first >= k) s++;
        }

        int query() {
            if (s > t) return 0x3f3f3f3f;
            return a[s].second;
        }
    } q;

    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + (t[i] != t[i - 1]);

    q.init(n + 1);
    dp[0] = 0; q.update(0, 2 * dp[0] - sum[1]);

    for (int i = 1; i <= n; i++) {
        dp[i] = 0x3f3f3f3f;
        if (s[i] == t[i]) {
            dp[i] = dp[i - 1];
            q.update(i, 2 * dp[i] - sum[i + 1]);
            continue;
        }
        dp[i] = min(dp[i], (q.query() + sum[i] + 3) / 2);
        q.update(i, 2 * dp[i] - sum[i + 1]);
    }

    return dp[n];
}

vector<char> generateInput(int n) {
    vector<char> s(n + 1), t(n + 1);
    for (int i = 1; i <= n; i++) {
        s[i] = rand() % 26 + 'a';
        t[i] = rand() % 26 + 'a';
    }
    t[0] = '*';
    return s, t;
}