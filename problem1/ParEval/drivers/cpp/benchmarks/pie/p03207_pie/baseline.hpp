#pragma once

#include <bits/stdc++.h>

#define ll long long int

using namespace std;

ll baseline(ll a, vector<ll>& ar) {
    ll sum = 0;
    sort(ar.begin() + 1, ar.begin() + a + 1);
    for (ll i = 1; i < a; i++) {
        sum += ar[i];
    }
    return sum + ar[a] / 2;
}

vector<ll> generateInput(ll a) {
    vector<ll> ar(a + 1);
    for (ll i = 1; i <= a; i++) {
        ar[i] = rand() % 1000000;
    }
    return ar;
}