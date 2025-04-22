#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long

vector<string> baseline(ll n, ll m, ll q, vector<ll>& queries){
    vector<ll> t(n + 2, 0);
    auto low = [](ll x) { return x & (-x); };
    auto query = [&](ll x) {
        ll res = 0;
        for(; x > 0; x -= low(x)) res += t[x];
        return res;
    };
    auto updata = [&](ll x, ll k) {
        for(; x <= n; x += low(x)) t[x] += k;
    };
    for(int i = 0; i < q; i++){
        updata(queries[i], 1);
    }
    vector<string> result;
    for(int i = 1; i <= n; i++){
        int t_val = query(i) - query(i - 1) + m - q;
        if(t_val <= 0) result.push_back("No");
        else result.push_back("Yes");
    }
    return result;
}

vector<ll> generateInput(ll n, ll q){
    vector<ll> queries(q);
    for(ll i = 0; i < q; i++){
        queries[i] = i + 1;
    }
    return queries;
}