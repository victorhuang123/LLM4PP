#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, n) for(int i = 0; i < (n); i++)

const ll mod = 1e9 + 7;

ll baseline(int N, vector<ll>& A) {
    int kazu[60] = {};
    rep(i, N) {
        rep(j, 60) {
            kazu[j] += A[i] >> j & 1;
        }
    }

    ll kotae[60] = {};
    rep(i, N) {
        rep(j, 60) {
            kazu[j] -= A[i] >> j & 1;
        }

        rep(j, 60) {
            if (A[i] >> j & 1) {
                kotae[j] += N - 1 - kazu[j];
            } else {
                kotae[j] += kazu[j];
            }
        }

        rep(j, 60) {
            kazu[j] += A[i] >> j & 1;
        }
    }

    ll ans = 0;
    rep(i, 60) {
        kotae[i] %= mod;
        ll tmp = (1ll << i) % mod;
        ans += kotae[i] * tmp % mod;
    }
    ans %= mod;
    return ans * 500000004 % mod; // 500000004 is the modular inverse of 2 modulo 1e9+7
}

vector<ll> generateInput(int N) {
    vector<ll> A(N);
    rep(i, N) {
        A[i] = i + 1;
    }
    return A;
}