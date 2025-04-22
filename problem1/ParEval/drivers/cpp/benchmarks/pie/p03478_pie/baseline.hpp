#pragma once

#include<bits/stdc++.h>

using namespace std;

#define pb push_back

#define rep(i,n) for(int i=0;i<n;i++)

#define rep1(i,n) for(int i=1;i<=n;i++)

#define mp make_pair

#define F first

#define S second

#define IOS ios_base::sync_with_stdio(0); cin.tie(0)

typedef long long ll;

vector<int> g[100005];

ll q,n;

ll baseline(ll n, ll A, ll B) {
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        ll a = i / 10000, b = (i % 10000) / 1000, c = (i % 1000) / 100, d = (i % 100) / 10, e = i % 10;
        if(a + b + c + d + e <= B && a + b + c + d + e >= A) sum += i;
    }
    return sum;
}

vector<ll> generateInput() {
    ll n = 1000000; // Large input to test efficiency
    ll A = 10;
    ll B = 45;
    return {n, A, B};
}