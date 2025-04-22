#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll baseline(int n, const vector<ll>& v)
{
    ll ans = 0;
    for (int i = 0; i < n; ++i) ans = __gcd(ans, v[i]);
    return ans;
}

vector<ll> generateInput(int n)
{
    vector<ll> v(n);
    for (int i = 0; i < n; ++i) v[i] = rand() % 1000000 + 1;
    return v;
}