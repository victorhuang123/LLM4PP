#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long

ll baseline(ll n) {
    ll c = 0;
    for (ll i = 1; i <= n; i++) {
        stringstream ss;
        string s1;
        ss << i;
        ss >> s1;
        ll k = s1.size();
        if (k % 2 != 0) {
            c++;
        }
    }
    return c;
}

vector<ll> generateInput() {
    return {1000000000}; // Example input to maximize the problem scale
}