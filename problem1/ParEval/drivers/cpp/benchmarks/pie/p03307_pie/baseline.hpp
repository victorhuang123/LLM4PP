#pragma once

#include<bits/stdc++.h>

typedef long long int ll;

using namespace std;

ll baseline(ll n) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for(ll i = n; ; i += n) {
        if(i % 2 == 0) {
            return i;
        }
    }
}

vector<ll> generateInput() {
    vector<ll> input;
    input.push_back(1e18); // Large input to test efficiency
    return input;
}