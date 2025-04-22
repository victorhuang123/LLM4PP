#pragma once

#include<bits/stdc++.h>

using namespace std;

#define MAX 100005

int baseline(int n, int q, vector<tuple<int, int, int, int>>& queries) {
    vector<int> bit(MAX, 0);

    auto Add = [&](int i, int x) {
        while (i) {
            bit[i] += x;
            i -= (i & -i);
        }
    };

    auto Get = [&](int i) {
        int res = 0;
        while (i < MAX) {
            res += bit[i];
            i += (i & -i);
        }
        return res;
    };

    int result = 0;
    for (const auto& query : queries) {
        int type = get<0>(query);
        if (type == 0) {
            int l = get<1>(query);
            int r = get<2>(query);
            int x = get<3>(query);
            Add(r, x);
            Add(l - 1, -x);
        } else {
            int target = get<1>(query);
            result += Get(target);
        }
    }
    return result;
}

vector<tuple<int, int, int, int>> generateInput(int n, int q) {
    vector<tuple<int, int, int, int>> queries;
    for (int i = 0; i < q; ++i) {
        int type = rand() % 2;
        if (type == 0) {
            int l = rand() % n + 1;
            int r = rand() % n + 1;
            if (l > r) swap(l, r);
            int x = rand() % 100000;
            queries.emplace_back(type, l, r, x);
        } else {
            int target = rand() % n + 1;
            queries.emplace_back(type, target, 0, 0);
        }
    }
    return queries;
}