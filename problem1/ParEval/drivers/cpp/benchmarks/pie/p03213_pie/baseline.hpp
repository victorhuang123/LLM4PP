#pragma once

#include <bits/stdc++.h>

typedef long long ll;

const int INF=1e9,MOD=1e9+7,ohara=1e6;

const ll LINF=1e18;

using namespace std;

#define rep(i,n) for(ll (i)=0;(i)<(int)(n);(i)++)

#define rrep(i,a,b) for(ll i=(a);i<(b);i++)

#define rrrep(i,a,b) for(ll i=(a);i>=(b);i--)

#define all(v) (v).begin(), (v).end()

#define pb(q) push_back(q)

#define Size(n) (n).size()

ll baseline(ll n) {
    vector<ll> ans(ohara, 1);
    ll cnt = 0;

    auto cal = [&](ll dat, ll n, vector<ll>& ans) {
        rrep(i, 2, n + 1) {
            if (dat <= 1) break;
            if (dat % i != 0) continue;
            while (1) {
                dat /= i;
                ans[i]++;
                if (dat % i != 0 || dat <= 1) break;
            }
        }
    };

    rrep(i, 2, n + 1) {
        cal(i, n, ans);
    }

    rep(i, n + 1) {
        rep(j, n + 1) {
            rep(k, n + 1) {
                if (i == j || j == k || i == k) continue;
                if (ans[i] >= 5 && ans[j] >= 5 && ans[k] >= 3) cnt++;
            }
        }
    }

    cnt /= 2;

    rep(i, n + 1) {
        rep(j, n + 1) {
            if (i == j) continue;
            if (ans[i] >= 3 && ans[j] >= 25) cnt++;
            if (ans[i] >= 5 && ans[j] >= 15) cnt++;
        }
    }

    rep(i, n + 1) {
        if (ans[i] >= 75) cnt++;
    }

    return cnt;
}

vector<ll> generateInput() {
    return {ohara};
}