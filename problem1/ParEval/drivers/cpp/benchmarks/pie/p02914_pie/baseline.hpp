#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

ll baseline(int N, const vector<ll>& a) {
    ll goukei = 0;
    rep(i, N) {
        goukei ^= a[i];
    }

    int M = 60;
    vector<vector<bool>> A(N, vector<bool>(M, false));
    rep(i, N) {
        rep(j, M) {
            A[i][j] = a[i] >> j & 1;
        }
    }

    int r = 0;
    for (int i = M - 1; i >= 0; i--) {
        if (!(goukei >> i & 1)) {
            for (int j = r; j < N; j++) {
                if (A[j][i]) {
                    rep(k, M) swap(A[r][k], A[j][k]);

                    for (int j = r + 1; j < N; j++) {
                        if (A[j][i]) {
                            rep(k, M) A[j][k] ^= A[r][k];
                        }
                    }
                    if (!A[0][i]) {
                        rep(k, M) A[0][k] ^= A[r][k];
                    }
                    r++;
                    break;
                }
            }
        }
    }

    ll kotae = 0;
    rep(i, M) {
        if (!(goukei >> i & 1)) {
            if (A[0][i]) {
                kotae += 1ll << (i + 1);
            }
        }
        else {
            kotae += 1ll << i;
        }
    }
    return kotae;
}

vector<ll> generateInput(int N) {
    vector<ll> a(N);
    rep(i, N) {
        a[i] = (1ll << 60) - 1 - i;
    }
    return a;
}