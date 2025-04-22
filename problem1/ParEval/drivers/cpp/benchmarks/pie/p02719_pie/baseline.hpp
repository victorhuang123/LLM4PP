#pragma once

#include<bits/stdc++.h>

#define ll long long

using namespace std;

ll baseline(ll n, ll k) {
    n = n % k;
    while (abs(n - k) < n) {
        n = abs(n - k);
    }
    return n;
}

vector<ll> generateInput() {
    return {1000000000000000000, 999999999999999999};
}