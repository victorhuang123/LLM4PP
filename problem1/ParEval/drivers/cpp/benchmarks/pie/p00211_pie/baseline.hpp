#pragma once
#include<vector>
#include<iostream>
using namespace std;

typedef long long ll;

ll baseline(int n, vector<ll>& d, vector<ll>& v, vector<ll>& t) {
    t[0] = 1;
    for(int i = 1; i < n; i++) {
        t[i] = t[i-1] * d[i-1] * v[i];
        for(int j = 0; j < i; j++) t[j] *= d[i] * v[i-1];
        ll T = t[0];
        for(int j = 1; j <= i; j++) {
            ll a = T, b = t[j];
            while(b>0) {
                ll temp = b;
                b = a % b;
                a = temp;
            }
            T = a;
        }
        for(int j = 0; j <= i; j++) t[j] /= T;
    }
    return t[n-1];
}

