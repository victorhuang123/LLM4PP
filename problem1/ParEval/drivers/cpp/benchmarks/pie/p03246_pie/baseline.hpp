#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using LL = ll;
using ull = unsigned long long;
using uLL = ull;
using pii = pair<int, int>;

constexpr int INF = 0x7F7F7F7F;
constexpr int maxn = int(1e5) + 1;

int baseline(const vector<int>& input) {
    vector<vector<int>> cnt(2, vector<int>(maxn, 0));
    int n = input.size();
    for (int i = 0; i < n; ++i) {
        int x = input[i];
        ++cnt[i & 1][x];
    }
    int ans = 0;
    int max_0 = max_element(cnt[0].begin(), cnt[0].end()) - cnt[0].begin();
    int max_1 = max_element(cnt[1].begin(), cnt[1].end()) - cnt[1].begin();
    if (max_1 != max_0) {
        ans = n - cnt[0][max_0] - cnt[1][max_1];
    } else {
        int m0 = cnt[0][max_0];
        int m1 = cnt[1][max_1];
        cnt[0][max_0] = cnt[1][max_1] = 0;
        max_0 = max_element(cnt[0].begin(), cnt[0].end()) - cnt[0].begin();
        max_1 = max_element(cnt[1].begin(), cnt[1].end()) - cnt[1].begin();
        ans = n - max(cnt[0][max_0] + m1, m0 + cnt[1][max_1]);
    }
    return ans;
}

vector<int> generate_input(int n) {
    vector<int> input(n);
    for (int i = 0; i < n; ++i) {
        input[i] = rand() % maxn;
    }
    return input;
}