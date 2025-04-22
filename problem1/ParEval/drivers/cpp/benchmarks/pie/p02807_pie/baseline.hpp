#pragma once

#include <bits/stdc++.h>

#define MOD 1000000007LL

using namespace std;

typedef int_fast64_t ll;

template<int N, typename T, T M>
struct ModFact {
    T inv[N+1];
    T fact[N+1];
    T ifact[N+1];

    constexpr ModFact() : fact(), ifact() {
        fact[0] = 1;
        for (int i = 0; i < N; i++)
            fact[i+1] = (fact[i]*(i+1))%M;
        ifact[N] = power(fact[N], M-2);
        for (int i = N-1; i >= 0; i--)
            ifact[i] = (ifact[i+1]*(i+1))%M;
        inv[0] = 0;
        for (int i = 0; i < N; i++)
            inv[i+1] = (fact[i]*ifact[i+1])%M;
    }

    constexpr T power(T a, T b) {
        T r = 1;
        while (b>0) {
            if((b&1)!=0) r = (r*a)%M;
            a = (a*a)%M;
            b >>= 1;
        }
        return r;
    }

    constexpr T comb(T n, T r) {
        return (((fact[n]*ifact[r])%M)*ifact[n-r])%M;
    }
};

ModFact<100000, ll, MOD> fact;

ll baseline(ll N, vector<ll>& X) {
    ll ans = 0;
    ll a = 0;
    for (int i = 0; i < N-1; i++) {
        a = (a + fact.inv[i+1]) % MOD;
        ans = (ans + a * (X[i+1] - X[i])) % MOD;
    }
    return (ans * fact.fact[N-1]) % MOD;
}

vector<ll> generateInput(ll N) {
    vector<ll> X(N);
    for (ll i = 0; i < N; i++) {
        X[i] = i + 1;
    }
    return X;
}