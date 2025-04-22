#pragma once

#include<vector>
#include<bitset>
#include<algorithm>
#define rep(i,l,r) for (int i=(l); i<=(r); i++)
using namespace std;

const int mod=998244353;

int baseline(int n, int m, const vector<vector<int>>& a) {
    vector<int> mi(m + 1, 1);
    rep(i, 1, m) mi[i] = 2ll * mi[i - 1] % mod;

    vector<bitset<305>> b(m);
    int k = 0;

    rep(i, 0, n - 1) {
        bitset<305> x;
        int l = -1;
        rep(j, 0, m - 1) x.set(j, a[i][j]);
        rep(j, 0, m - 1) if (x[j]) {
            if (b[j].any()) x ^= b[j];
            else {
                b[j] = x;
                l = j;
                break;
            }
        }
        if (l == -1) k++;
    }

    int ans = (1ll * mi[m] * mi[k] + 1ll * mi[m - 1] * (mi[n] + mod - mi[k])) % mod;
    return (1ll * mi[n] * mi[m] + mod - ans) % mod;
}

vector<vector<int>> generateInput(int n, int m) {
    vector<vector<int>> a(n, vector<int>(m, 1));
    return a;
}