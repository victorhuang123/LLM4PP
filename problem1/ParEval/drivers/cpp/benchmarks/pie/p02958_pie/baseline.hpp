#pragma once

#include<bits/stdc++.h>

#define ll long long int

using namespace std;

vector<ll> generateInput() {
    ll n = 100000;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        a[i] = i;
    }
    random_shuffle(a.begin(), a.end());
    return a;
}

bool baseline(const vector<ll>& a) {
    ll n = a.size();
    vector<ll> b = a;
    sort(b.begin(), b.end());
    
    ll c = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            c++;
        }
    }
    
    if (c == 0) {
        return true;
    } else if (c == 2) {
        return true;
    } else {
        return false;
    }
}