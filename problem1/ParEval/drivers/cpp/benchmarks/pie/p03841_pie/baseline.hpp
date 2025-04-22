

#include <bits/stdc++.h>

using namespace std;

bool baseline(int N, vector<int>& positions) {
    vector<int> cnt(N + 1, 0);
    vector<int> a(N * N + 1, -1);
    vector<pair<int, int>> g;

    for (int i = 1; i <= N; ++i) {
        cnt[i] = 1;
        int x = positions[i - 1];
        a[x] = i;
        g.emplace_back(x, i);
    }

    sort(g.begin(), g.end());

    for (auto& p : g) {
        int curPos = p.first;
        int x = p.second;
        int cur = x;
        for (int j = 1; j < curPos; ++j) {
            if (a[j] != -1) continue;
            if (cnt[cur] < cur) {
                a[j] = cur;
                cnt[cur]++;
            }
        }
        if (cnt[cur] != cur) {
            return false;
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = positions[i - 1] + 1; j <= N * N; ++j) {
            if (a[j] != -1) continue;
            if (cnt[i] < N) {
                a[j] = i;
                cnt[i]++;
            }
        }
        if (cnt[i] < N) {
            return false;
        }
    }

    return true;
}