#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=1e9+7;

ll baseline(ll n, ll k, vector<ll>& a) {
    vector<ll> b(n, 0);

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(a[i]>a[j])
                b[i]++;
        }
    }

    ll sum=0;
    ll cnt=0;
    cnt=k%mod*((k-1)%mod)/2%mod;

    for(int i=0;i<n;i++) {
        sum=sum+(b[i]%mod)*((cnt)%mod)%mod;
    }

    ll sum1=0;
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if(a[i]>a[j])
                sum1++;
        }
    }

    sum1=k%mod*(sum1%mod)%mod;
    sum=(sum+sum1)%mod;

    return sum%mod;
}

vector<ll> generateInput(ll n) {
    vector<ll> a(n);
    for(ll i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}