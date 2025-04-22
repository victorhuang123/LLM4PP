#pragma once

#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll;

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

double baseline(ll n, ll m, vector<ll>& p) {
    double ans;
    sort(p.begin(), p.end());
    ans = ((n + 1) * n) / 2;

    ll num = 0;
    for (int i = 1; i < (1 << m); i++) {
        int bit = 0;
        for (int j = i; j != 0; j >>= 1) bit += j & 1;
        ll tmp = 1;
        for (int j = 0; j < m; j++)
            if (i >> j & 1) tmp = lcm(tmp, p[j]);

        if (bit & 1) {
            num += n / tmp;
            ans -= (n / tmp + 1) * n / 2;
        } else {
            num -= n / tmp;
            ans += (n / tmp + 1) * n / 2;
        }
    }

    if (num == n) return 0.00000000;
    else return ans / (n - num);
}

vector<ll> generateInput(ll& n, ll& m) {
    n = 1000000;
    m = 20;
    vector<ll> p(m);
    for (int i = 0; i < m; i++) {
        p[i] = i + 2;
    }
    return p;
}