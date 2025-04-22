#pragma once

#include<bits/stdc++.h>

#define rep(i,n) for(int i = 0; i < (n); i++)
#define rrep(i,n) for(int i = (n)-1; i >= 0; i--)
#define rep1(i,n) for(int i = 1; i <= (n); i++)
#define rrep1(i,n) for(int i = (n); i > 0; i--)

#define ll long long
#define pi pair<int, int>
#define pll pair<ll, ll>

#define MOD 1000000007
#define INF 1000000000000000LL

using namespace std;

ll baseline(ll n, ll k, vector<int>& a) {
    ll sum = 0;
    rep(i, n) sum += a[i];

    set<ll> c;
    for(ll i = 1; i * i <= sum; i++) {
        if(sum % i) continue;
        c.insert(i);
        c.insert(sum / i);
    }

    ll ans = 0;
    for(ll cc : c) {
        vector<ll> ca(n);
        rep(i, n) ca[i] = a[i] % cc;
        sort(ca.begin(), ca.end());

        ll psum = 0, msum = 0;
        rep(i, n) psum += ca[i];
        if(psum <= k) ans = max<ll>(ans, cc);
        rrep(i, n) {
            psum -= ca[i];
            msum += cc - ca[i];
            ll cans = max<ll>(psum, msum);
            if(cans <= k) ans = max<ll>(ans, cc);
        }
    }

    return ans;
}

vector<int> generateInput(ll n) {
    vector<int> a(n);
    rep(i, n) a[i] = rand() % 1000000 + 1;
    return a;
}