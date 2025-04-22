#pragma once

#include<bits/stdc++.h>

#define ll long long int

using namespace std;

ll baseline(ll n, const vector<bool>& ara3) {
    ll counter = 0;
    for(ll i = 1, j = n; i <= n; i++, j--) {
        if(ara3[i] && ara3[j]) {
            counter++;
        }
    }
    return counter;
}

vector<bool> generateInput(ll n) {
    vector<bool> ara3(n + 1, true);
    ara3[1] = false;
    for(ll i = 2; i <= n; i++) {
        if(ara3[i]) {
            for(ll j = 2; i * j <= n; j++) {
                ara3[i * j] = false;
            }
        }
    }
    return ara3;
}