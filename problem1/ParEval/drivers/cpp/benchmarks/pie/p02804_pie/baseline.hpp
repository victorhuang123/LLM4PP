#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;
const int IMAX = 100000;

constexpr ll modpow(ll A, ll B) {
    ll kotae = 1;
    while (B > 0) {
        if (B & 1) kotae = kotae * A % mod;
        A = A * A % mod;
        B >>= 1;
    }
    return kotae;
}

class unko {
public:
    int fac[IMAX + 1], ifac[IMAX + 1], inv[IMAX + 1];
    constexpr unko() : fac(), ifac(), inv() {
        fac[0] = 1;
        for (int i = 1; i <= IMAX; i++) fac[i] = ll(fac[i - 1]) * i % mod;
        ifac[IMAX] = modpow(fac[IMAX], mod - 2);
        for (int i = IMAX; i > 0; i--) ifac[i - 1] = ll(ifac[i]) * i % mod;
        inv[0] = 1;
        for (int i = 1; i <= IMAX; i++) inv[i] = ll(ifac[i]) * fac[i - 1] % mod;
    }
    int comb(int A, int B) {
        return ll(fac[A]) * ifac[B] % mod * ifac[A - B] % mod;
    }
} f;

ll baseline(int N, int K, vector<int>& A) {
    sort(A.begin(), A.end());
    ll kotae = 0;
    for (int i = K - 1; i < N; i++) {
        kotae += (ll)f.comb(i, K - 1) * A[i] % mod;
    }
    kotae %= mod;
    for (int i = N - K; i >= 0; i--) {
        kotae -= (ll)f.comb(N - i - 1, K - 1) * A[i] % mod;
    }
    kotae %= mod;
    return (kotae + mod) % mod;
}

vector<int> generate_input(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % mod;
    }
    return A;
}