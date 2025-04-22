#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

ll baseline(ll N, ll X, const vector<ll>& x) {
    vector<ll> diff(N);
    for(int i = 0; i < N; ++i) {
        diff[i] = abs(x[i] - X);
    }
    ll ans = diff[0];
    for(int i = 0; i < N; ++i) {
        if(ans < diff[i]) ans = GCD(diff[i], ans);
        else ans = GCD(ans, diff[i]);
    }
    return ans;
}

ll GCD(ll a, ll b){
    if(b==0) return a;
    return GCD(b, a%b);
}

vector<ll> generateInput(ll N, ll X) {
    vector<ll> x(N);
    for(ll i = 0; i < N; ++i) {
        x[i] = X - i;
    }
    return x;
}