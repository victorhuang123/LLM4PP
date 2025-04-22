#pragma once

#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll mod = 1e9 + 7;

ll modpow(ll A, ll B) {
    ll kotae = 1;
    while (B > 0) {
        if (B & 1) kotae = kotae * A % mod;
        A = A * A % mod;
        B >>= 1;
    }
    return kotae;
}

ll baseline(int N, const vector<int>& A, int kazu) {
    const int IMAX = 100001;
    vector<ll> fac(IMAX + 1), ifac(IMAX + 1);

    fac[0] = 1;
    for (int i = 1; i <= IMAX; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[IMAX] = modpow(fac[IMAX], mod - 2);
    for (int i = IMAX; i > 0; i--) ifac[i - 1] = ifac[i] * i % mod;

    auto comb = [&](int A, int B) {
        return fac[A] * ifac[B] % mod * ifac[A - B] % mod;
    };

    ll result = 0;
    for (int i = 1; i <= N + 1; i++) {
        ll kotae = comb(N + 1, i);
        if (kazu >= i - 1) {
            kotae = kotae - comb(kazu, i - 1);
            if (kotae < 0) kotae += mod;
        }
        result = (result + kotae) % mod;
    }

    return result;
}

vector<int> generateInput(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = i + 1;
    }
    return A;
}