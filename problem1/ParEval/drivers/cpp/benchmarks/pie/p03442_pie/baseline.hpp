#pragma once

#include<bits/stdc++.h>

using namespace std;

const int M = 16;

void chkmin(int &x, int y) {
    if (y < x) x = y;
}

int baseline(int n, const vector<int>& s, const vector<int>& cnt, vector<int>& f) {
    int now = 0, ans = 0;
    for (int i = 1; i < 16; i++) {
        ans += cnt[i] / 2;
        now += ((cnt[i] & 1) << (i - 1));
    }

    fill(f.begin(), f.end(), 2000000000);
    f[now] = 0;

    for (int i = (1 << 15) - 1; i; i--) {
        if (f[i] < 2000000000) {
            for (int j = 1; j <= 15; j++) {
                if (i & (1 << (j - 1))) {
                    for (int k = 1; k <= 15; k++) {
                        if (i & (1 << (k - 1)) && j != k) {
                            int l = j ^ k;
                            if (i & (1 << (l - 1))) {
                                chkmin(f[i - (1 << (j - 1)) - (1 << (k - 1)) - (1 << (l - 1))], f[i] + 2);
                            } else {
                                chkmin(f[i - (1 << (j - 1)) - (1 << (k - 1)) + (1 << (l - 1))], f[i] + 1);
                            }
                        }
                    }
                }
            }
        }
    }
    return f[0] + ans;
}

vector<int> generateInput(int n) {
    vector<int> s(n);
    vector<int> cnt(M, 0);
    vector<int> f(1 << 15, 0);

    for (int i = 1; i < n; i++) {
        int u = rand() % n;
        int v = rand() % n;
        int w = rand() % 16;
        s[u] ^= w;
        s[v] ^= w;
    }

    for (int i = 0; i < n; i++) {
        cnt[s[i]]++;
    }

    return s;
}