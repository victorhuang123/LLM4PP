#pragma once

#include<bits/stdc++.h>

using namespace std;

#define FastRead        ios_base::sync_with_stdio(0);cin.tie(NULL);
#define endl            "\n"
#define NUM             1000005

typedef long long ll;

ll baseline(ll a, ll b)
{
    map<ll,ll> mp;
    ll gcd = __gcd(a,b);

    while(gcd%2==0)
    {
        mp[2]++;
        gcd/=2;
    }

    for(ll i=3;i<=sqrt(gcd);i+=2)
    {
        while(gcd%i==0)
        {
            mp[i]++;
            gcd/=i;
        }
    }

    if(gcd>2)
        mp[gcd]++;

    return 1 + mp.size();
}

vector<ll> generateInput()
{
    vector<ll> input;
    input.push_back(123456789012345678);
    input.push_back(987654321098765432);
    return input;
}