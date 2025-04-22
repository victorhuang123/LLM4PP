#pragma once

#include<vector>
#include<algorithm>

using namespace std;

typedef long long ll;

const int mod = 998244353;

ll modpow(ll A, ll B) {
    ll kotae = 1;
    while (B > 0) {
        if (B & 1) kotae = kotae * A % mod;
        A = A * A % mod;
        B >>= 1;
    }
    return kotae;
}

ll baseline(int N, int M, int K) {
    if (M == 1) {
        return (K == N - 1) ? 1 : 0;
    }
    if (N == 1) {
        return M;
    }

    vector<int> fac(N + 1, 1);
    vector<int> ifac(N + 1, 1);

    for (int i = 1; i <= N; i++) fac[i] = ll(fac[i - 1]) * i % mod;
    ifac[N] = modpow(fac[N], mod - 2);
    for (int i = N; i > 0; i--) ifac[i - 1] = ll(ifac[i]) * i % mod;

    ll kotae = 0;
    ll tmp = ll(M) * fac[N - 1] % mod * modpow(M - 1, N - K - 1) % mod;
    for (int k = K; k >= 0; k--) {
        kotae += tmp * ifac[k] % mod * ifac[N - 1 - k] % mod;
        tmp = tmp * (M - 1) % mod;
    }

    return kotae % mod;
}

vector<int> generateInput() {
    int N = 200000;
    int M = 1000000000;
    int K = 100000;
    return {N, M, K};
}