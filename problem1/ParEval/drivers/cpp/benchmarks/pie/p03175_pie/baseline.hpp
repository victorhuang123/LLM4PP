#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

ll mod = 1e9 + 7;

pair<ll, ll> baseline(int N, vector<int> V[], int D[], int start) {
    if (D[start]) return mp(0, 1);
    D[start] = 1;
    ll kuro = 1;
    ll siro = 1;
    for (int i : V[start]) {
        auto k = baseline(N, V, D, i);
        kuro = (kuro * k.second) % mod;
        siro = (siro * (k.first + k.second)) % mod;
    }
    return mp(kuro, siro);
}

vector<int>* generateInput(int N) {
    vector<int>* V = new vector<int>[N];
    rep(i, N) {
        rep(j, N) {
            if (i != j) {
                V[i].pb(j);
            }
        }
    }
    return V;
}