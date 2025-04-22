#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007

ll baseline(ll n, ll m, vector<ll>& ara, vector<ll>& arb) {
    ll ANS = 0, ans = 0;
    ll mul = -n + 1;
    for(int i = 0; i < n; i++) {
        ara[i] = (ara[i] * mul) % MOD;
        mul += 2;
    }

    mul = -m + 1;
    for(int i = 0; i < m; i++) {
        arb[i] = (arb[i] * mul) % MOD;
        mul += 2;
    }

    for(int i = 0; i < n; i++) ans = (ans + ara[i]) % MOD;
    for(int i = 0; i < m; i++) ANS = (ANS + (arb[i] * ans) % MOD) % MOD;

    return ANS;
}

vector<ll> generateInput(ll size) {
    vector<ll> input(size);
    for(ll i = 0; i < size; i++) {
        input[i] = rand() % MOD;
    }
    return input;
}