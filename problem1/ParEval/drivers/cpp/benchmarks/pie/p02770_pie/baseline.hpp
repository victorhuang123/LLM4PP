#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

vector<int> generate_input(int k, int q) {
    vector<int> initial_d(k);
    for (int i = 0; i < k; i++) {
        initial_d[i] = rand() % 1000000 + 1;
    }

    return initial_d;
}

ll baseline(int k, int q, vector<int>& initial_d, vector<tuple<int, int, int>>& queries) {
    const int N = 1e4+10;
    vector<int> d(N*2);

    for (int i = 0; i < k; i++) {
        d[i] = initial_d[i];
    }

    int nk = k;
    while (nk < N) nk += k;

    for (int i = k; i < nk; i++) {
        d[i] = d[i%k];
    }

    k = nk;

    ll total_ans = 0;

    for (auto& query : queries) {
        int n, x, m;
        tie(n, x, m) = query;
        n--;
        x %= m;
        ll tot = 0;
        int zcnt = 0;

        for (int i = 0; i < k; i++) {
            tot += (d[i] % m);
            zcnt += (d[i] % m == 0);
        }

        int num_cyc = n / k, rem_cyc = n % k;
        ll ans = num_cyc * k - (x + tot * num_cyc) / m - num_cyc * zcnt;
        x = (x + tot * num_cyc) % m;

        for (int i = 0; i < rem_cyc; i++) {
            int nx = (x + d[i]) % m;
            ans += (x < nx);
            x = nx;
        }

        total_ans += ans;
    }

    return total_ans;
}