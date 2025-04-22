#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long int

ll baseline(const vector<ll>& ara) {
    ll t = ara.size() - 1;
    vector<ll> dp(t + 1, -1);

    function<ll(ll)> call = [&](ll id) {
        if(id == t) return 0LL;
        if(dp[id] != -1) return dp[id];

        ll p = call(id + 1) + abs(ara[id + 1] - ara[id]);
        ll q = 100000000LL;

        if(id + 2 <= t)
            q = call(id + 2) + abs(ara[id + 2] - ara[id]);

        dp[id] = min(p, q);
        return dp[id];
    };

    return call(1);
}

vector<ll> generateInput() {
    ll t = 1000000;
    vector<ll> ara(t + 1);
    for(ll i = 1; i <= t; i++) {
        ara[i] = rand() % 1000000;
    }
    return ara;
}