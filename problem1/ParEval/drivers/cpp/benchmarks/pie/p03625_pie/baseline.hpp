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

vector<ll> generateInput(ll n) {
    vector<ll> input(n);
    rep(i, n) {
        input[i] = rand() % 1000000 + 1;
    }
    return input;
}

ll baseline(ll n, const vector<ll>& input) {
    map<ll,ll> m;
    vector<ll> ans;
    rep(i,n) {
        ll tmp = input[i];
        m[tmp]++;
        if(m[tmp]%2==0) ans.pb(tmp);
    }
    sort(ans.begin(),ans.end());
    if(ans.size()<2) return 0;
    else return ans[ans.size()-1]*ans[ans.size()-2];
}