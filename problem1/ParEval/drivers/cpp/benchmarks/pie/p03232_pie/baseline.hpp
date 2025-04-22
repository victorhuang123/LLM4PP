#pragma once

#include<vector>
#include<algorithm>

#define mod 1000000007
typedef long long ll;

using namespace std;

ll baseline(ll n, const vector<ll>& a) {
    vector<ll> f(N), g(N), h(N), cs(N);
    
    f[0] = 1;
    for(ll i = 1; i < N; i++) f[i] = f[i-1] * i % mod;
    
    g[n+1] = 1;
    for(ll i = n; i >= 1; i--) g[i] = g[i+1] * i % mod;
    
    for(ll i = 1; i < n; i++) {
        h[i+1] = f[i] * g[i+2] % mod;
    }
    h[1] = g[2];
    
    cs[0] = cs[1] = 0;
    for(ll i = 2; i < N; i++) cs[i] = (cs[i-1] + h[i]) % mod;
    
    ll ans = 0;
    for(ll i = 0; i < n; i++) {
        ll cur = cs[i+1] + cs[n-i] + h[1];
        ans = (ans + cur * a[i]) % mod;
    }
    
    return ans;
}

vector<ll> generateInput(ll n) {
    vector<ll> a(n);
    for(ll i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}