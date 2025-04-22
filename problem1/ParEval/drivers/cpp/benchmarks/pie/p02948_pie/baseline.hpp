#pragma once
#include <bits/stdc++.h>
using namespace std;

#define MAX 100005

int baseline(int n, int m, const vector<pair<int, int>>& items) {
    struct node {
        int cost, val;
        bool operator<(const node& a) const {
            return val == a.val ? cost < a.cost : val > a.val;
        }
    } A[MAX];

    int f[MAX];

    // Fixed find function with iterative path compression
    auto find = [&](int x) {
        while (f[x] != x) {
            f[x] = f[f[x]];  // Path compression
            x = f[x];
        }
        return x;
    };

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        A[i].cost = items[i-1].first;
        A[i].val = items[i-1].second;
    }

    iota(f, f + m + 2, 0);  // More efficient initialization
    sort(A + 1, A + n + 1);

    for(int i = 1; i <= n; i++) {
        int c = A[i].cost;
        if(c > m) continue;

        int root = find(c);
        if(root > m) continue;

        ans += A[i].val;
        f[root] = root + 1;  // Union with next position
    }

    return ans;
}