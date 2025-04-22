#pragma once

#include<bits/stdc++.h>

#define fo(i,a,b)for(int i=a,_e=b;i<=_e;++i)

#define ll long long

using namespace std;

const int N=50;

ll baseline(int n, vector<vector<char>>& a) {
    ll f[N][N][N], ans = 0;
    memset(f, 255, sizeof f);

    auto calc = [&](int l, int i, int r) -> ll {
        if(l == r) return 1;
        if(l == i || i == r) return 0;
        if(f[l][i][r] != -1) return f[l][i][r];

        ll tot = 0;
        fo(j, l, i-1)
            fo(p, j, i-1)
                fo(q, i+1, r)
                    fo(k, q, r)
                        if(a[j][k] == '1')
                            tot += calc(l, j, p) * calc(q, k, r) * calc(p+1, i, q-1);

        return f[l][i][r] = tot;
    };

    n *= 2;
    fo(i, 2, n)
        if(a[1][i] == '1')
            ans += calc(2, i, n);

    return ans;
}

vector<vector<char>> generateInput(int n) {
    vector<vector<char>> a(n * 2 + 1, vector<char>(n * 2 + 1, '0'));
    for (int i = 1; i <= n * 2; ++i) {
        for (int j = 1; j <= n * 2; ++j) {
            if (i < j && (i + j) % 2 == 0) {
                a[i][j] = '1';
            }
        }
    }
    return a;
}