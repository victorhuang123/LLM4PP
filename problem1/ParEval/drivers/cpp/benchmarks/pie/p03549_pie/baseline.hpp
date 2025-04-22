#pragma once

#include <bits/stdc++.h>

#define rep(i,n) for(int i=0; i<(n); i++)

#define all(v) v.begin(),v.end()

using namespace std;
typedef long long ll;

double baseline(int N, int M) {
    double ans = 0;
    double a = (double)((N-M)*100+1900*M);
    double b = 1;
    rep(i,M) b/=2;
    double c = 1-b;

    for (int i = 1; i < 1000000; i++) {
        double j = double(i);
        ans += j*a*b;
        b *= c;
    }
    return ans;
}