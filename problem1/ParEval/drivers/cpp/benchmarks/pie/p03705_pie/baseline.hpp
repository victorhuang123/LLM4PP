#pragma once

#include <bits/stdc++.h>

using namespace std;

#define ll long long

vector<ll> generateInput() {
    ll n = 1e6, a = 1, b = 1e6;
    return {n, a, b};
}

ll baseline(ll n, ll a, ll b) {
    if (n == 1) {
        if (a == b) return 1;
        else return 0;
    } else {
        if (a > b) return 0;
        else {
            return (b - a) * (n - 2) + 1;
        }
    }
}