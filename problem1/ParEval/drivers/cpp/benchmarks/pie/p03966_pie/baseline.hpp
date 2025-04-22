#pragma once

#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define ll long long
#define maxn 500005
#define fr(i,j,k) for(int i=j;i<k;i++)
#define f(n) fr(i,0,n)
#define f1(n) fr(i,1,n+1)
#define ms(i) memset(i,0,sizeof(i));
#define ms1(i) memset(i,-1,sizeof(i));
#define F first
#define S second

ll baseline(int n, vector<pair<ll, ll>>& pairs) {
    ll num1 = 0, num2 = 0;
    f(n) {
        ll a = pairs[i].F, b = pairs[i].S;
        ll l = 0, r = 1e18 / max(a, b) + 5;
        while (l < r - 1) {
            ll m = (l + r) >> 1;
            ll aa = a * m, bb = b * m;
            if (aa >= num1 && bb >= num2) {
                r = m;
            } else {
                l = m;
            }
        }
        num1 = r * a;
        num2 = r * b;
    }
    return num1 + num2;
}

vector<pair<ll, ll>> generateInput(int n) {
    vector<pair<ll, ll>> pairs(n);
    for (int i = 0; i < n; ++i) {
        pairs[i] = {rand() % 1000000 + 1, rand() % 1000000 + 1};
    }
    return pairs;
}