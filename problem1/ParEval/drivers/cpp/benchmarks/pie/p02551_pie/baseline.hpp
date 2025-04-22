#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long

const int maxn = 2e5 + 5;

int minTA[maxn], minPA[maxn];
int minTB[maxn], minPB[maxn];

int lowbit(int x) { return x & -x; }

void modify(int x, int c, int n, int minn[]) {
    while (x <= n) {
        minn[x] = min(minn[x], c);
        x += lowbit(x);
    }
}

int ask(int x, int n, int minn[]) {
    int ans = 1e9;
    while (x) {
        ans = min(ans, minn[x]);
        x -= lowbit(x);
    }
    return ans;
}

ll baseline(ll n, ll q, vector<pair<int, int>>& queries) {
    for (int i = 0; i < maxn; i++) {
        minTA[i] = minTB[i] = minPA[i] = minPB[i] = 1e9;
    }

    ll ans = (n - 2) * (n - 2);

    for (int g = 1; g <= q; g++) {
        int op = queries[g-1].first, x = queries[g-1].second;

        if (op == 1) {
            int res = ask(x, n, minTA);
            if (res == 1e9) res = g - 1;
            int res2 = minPB[res];
            if (res2 == 1e9) ans -= n - 2;
            else ans -= res2 - 2;
            modify(x, g, n, minTA);
            minPA[g] = x;
        } else {
            int res = ask(x, n, minTB);
            if (res == 1e9) res = g - 1;
            int res2 = minPA[res];
            if (res2 == 1e9) ans -= n - 2;
            else ans -= res2 - 2;
            modify(x, g, n, minTB);
            minPB[g] = x;
        }

        minPB[g] = min(minPB[g], minPB[g - 1]);
        minPA[g] = min(minPA[g], minPA[g - 1]);
    }

    return ans;
}

vector<pair<int, int>> generateInput(ll n, ll q) {
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++) {
        int op = rand() % 2 + 1;
        int x = rand() % (int)n + 1;
        queries.push_back({op, x});
    }
    return queries;
}