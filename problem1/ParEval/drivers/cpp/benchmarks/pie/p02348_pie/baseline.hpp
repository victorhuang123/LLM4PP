#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int n, int q, vector<pair<int, pair<int, int>>>& queries) {
    vector<int> t(1 << 18, 0);
    vector<int> value(q + 1);
    value[0] = 2147483647;

    auto Set = [&](int a, int b, int x, int k=0, int l=0, int r=(1<<17)) {
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            t[k] = max(t[k], x);
            return;
        }
        int m = (l + r) / 2;
        Set(a, b, x, k * 2 + 1, l, m);
        Set(a, b, x, k * 2 + 2, m, r);
    };

    auto Get = [&](int i) {
        i += (1 << 17) - 1;
        int res = t[i];
        while (i) {
            i = (i - 1) / 2;
            res = max(res, t[i]);
        }
        return res;
    };

    for (int i = 1; i <= q; i++) {
        int type = queries[i - 1].first;
        if (type == 0) {
            int l = queries[i - 1].second.first;
            int r = queries[i - 1].second.second;
            value[i] = queries[i - 1].second.second;
            r++;
            Set(l, r, i);
        } else {
            int target = queries[i - 1].second.first;
            int ans = Get(target);
            value[i] = value[ans];
        }
    }

    return value[q];
}

vector<pair<int, pair<int, int>>> generateInput(int n, int q) {
    vector<pair<int, pair<int, int>>> queries(q);
    for (int i = 0; i < q; i++) {
        int type = rand() % 2;
        int l = rand() % n;
        int r = rand() % n;
        if (l > r) swap(l, r);
        queries[i] = {type, {l, r}};
    }
    return queries;
}