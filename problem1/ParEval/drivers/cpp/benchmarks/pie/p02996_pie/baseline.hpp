#pragma once

#include <bits/stdc++.h>

using namespace std;

#define sz(a) int(a.size())
#define ll long long
#define ull unsigned long long
#define mod (ll)(1000000007)
#define endl '\n'
#define ENGZ ios::sync_with_stdio(0);ios_base::sync_with_stdio(0);cin.tie(0) , cout.tie(0);
#define pi double(acos(-1))
#define S second
#define F first
#define mem(arr,a) memset(arr,a,sizeof arr)

vector<pair<ll, ll>> generateInput() {
    ll n = 1e5;
    vector<pair<ll, ll>> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i].F = rand() % mod;
        arr[i].S = rand() % mod;
    }
    return arr;
}

bool baseline(ll n, vector<pair<ll, ll>> arr) {
    ENGZ;
    sort(arr.begin(), arr.end());
    bool f = 1;
    ll a = 0;
    for(int i = 0; i < n; i++) {
        a += arr[i].S;
        if(a > arr[i].F)
            f = 0;
    }
    return f;
}