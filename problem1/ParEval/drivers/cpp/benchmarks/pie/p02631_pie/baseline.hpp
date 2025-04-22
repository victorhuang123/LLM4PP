#pragma once

#include<vector>
#include<string>
using namespace std;

typedef long long ll;

string baseline(ll n, vector<ll>& a) {
    ll b = 0;
    for (ll i = 0; i < n; i++) b ^= a[i];
    string ans = "";
    for (ll i = 0; i < n; i++) {
        ans += to_string(a[i] ^ b);
        ans += " ";
    }
    return ans;
}

vector<ll> generateInput(ll n) {
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}