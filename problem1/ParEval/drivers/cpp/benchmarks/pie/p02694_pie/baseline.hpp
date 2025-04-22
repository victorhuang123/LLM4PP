#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;

const ll mod = 1e9+7;

const ll mod1 = 998244353;

const ll inf = 9e18+5;

#define rep(i,a,b) for(ll i=a;i<b;i++)

ll baseline(ll st) {
    ll X = 100;
    ll ans = 0;
    ll temp;
    while (1) {
        temp = X / 100;
        X += temp;
        ans++;
        if (X >= st) break;
    }
    return ans;
}

vector<ll> generate_input() {
    vector<ll> input;
    input.push_back(1e18); // Maximize the problem scale
    return input;
}