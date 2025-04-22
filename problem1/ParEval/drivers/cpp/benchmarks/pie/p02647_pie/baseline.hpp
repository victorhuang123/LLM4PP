#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, srt, end) for (long long i = (srt); i < (long long)(end); i++)

vector<ll> generateInput(ll n) {
    vector<ll> a(n);
    rep(i, 0, n) {
        a[i] = rand() % n + 1;
    }
    return a;
}

vector<ll> baseline(ll n, ll k, vector<ll> a) {
    ll itr = 0;
    bool exi = true;
    while(itr < k && exi){
        bool f = false;
        vector<ll> imos(n+1, 0);
        rep(i, 0, n){
            if(a[i] != n) f = true;
            imos[max(0LL, i - a[i])]++;
            imos[min(n, i + a[i] + 1)]--;
        }
        ll acc = 0;
        rep(i, 0, n){
            acc += imos[i];
            a[i] = acc;
        }
        exi = f;
        itr++;
    }
    return a;
}