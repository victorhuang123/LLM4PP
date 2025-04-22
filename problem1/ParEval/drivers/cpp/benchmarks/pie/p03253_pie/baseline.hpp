#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long

const ll N=20,P=1e9+7;

ll baseline(ll n, ll m)
{
    vector<ll> a(1<<N, 1);
    for(int i=1;i<1<<N;++i)
    {
        a[i]=a[i-1]*i%P;
    }
    ll ans=1;
    for(ll i=2;i*i<=m;++i)
    {
        if(!(m%i))
        {
            ll k=0;
            while(!(m%i))
            {
                ++k;
                m/=i;
            }
            ans*=a[n+k-1]%P;
            ans%=P;
            ans*=pow(a[n-1],P-2);
            ans%=P;
            ans*=pow(a[k],P-2);
            ans%=P;
        }
    }
    if(m>1)
    {
        ans*=n;
        ans%=P;
    }
    return ans;
}

inline ll pow(ll x,ll y)
{
    ll k=1;
    while(y)
    {
        if(y&1)
        {
            k*=x;
            k%=P;
        }
        y>>=1;
        x*=x;
        x%=P;
    }
    return k;
}