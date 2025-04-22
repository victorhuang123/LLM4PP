#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long

const int N=1009;

const int M=100009;

ll baseline(int n, vector<ll>& a) {
    vector<int> f(M, 0);
    vector<ll> pri;
    int tot = 0;

    f[1] = 1;
    for(int i = 2; i <= M - 9; i++) {
        if(!f[i]) pri.push_back(i);
        for(int j = 0; j < pri.size() && pri[j] * i <= M - 9; j++) {
            f[pri[j] * i] = 1;
            if(i % pri[j] == 0) break;
        }
    }

    for(int i = 0; i < n; i++) {
        ll t = a[i];
        for(int j = 0; j < pri.size(); j++) {
            if(t % pri[j] == 0) {
                while(!(t % pri[j])) t /= pri[j];
                if(t < M - 9) break;
            }
        }
        if(t > M - 9) pri.push_back(t);
    }

    ll ans = 0;
    for(int i = 0; i < pri.size(); i++) {
        ll area = 0;
        for(int j = 0; j < n; j++) {
            if(a[j] % pri[i] == 0) area += a[j];
        }
        ans = max(ans, area);
    }

    return ans;
}

vector<ll> generateInput(int n) {
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        a[i] = 1000000007 + i * 2;
    }
    return a;
}