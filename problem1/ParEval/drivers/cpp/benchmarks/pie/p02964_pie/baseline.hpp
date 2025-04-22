#pragma once

#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define pb push_back
#define fi first
#define se second
typedef long long ll;
const int N = 2e5 + 100;

vector<ll> generate_input() {
    ll n = 2e5, k = 1e9;
    vector<ll> a(n);
    rep(i, 0, n - 1) a[i] = i % 100 + 1;
    return a;
}

vector<ll> baseline(ll n, ll k, vector<ll>& a) {
    vector<ll> r[N], ans;
    pair<ll, ll> p[N];
    ll fst[N], tot = 0, pos = 0;
    memset(fst, -1, sizeof(fst));

    rep(i, 0, n - 1) r[a[i]].pb(i);

    rep(i, 1, N - 100) {
        if (!r[i].size()) continue; 
        int len = r[i].size();
        rep(j, 0, len - 1) {
            if (j != len - 1)
                p[r[i][j]].fi = (r[i][j + 1] + 1) % n,
                p[r[i][j]].se = r[i][j + 1] + 1 - r[i][j];
            else
                p[r[i][j]].fi = (r[i][0] + 1) % n,
                p[r[i][j]].se = n - r[i][j] + r[i][0] + 1;
        }
    }

    ll s = n * k - 1;
    while (tot + p[pos].se <= s) {
        if (fst[pos] != -1) {
            ll K = tot - fst[pos], h = (n * k - fst[pos]) % K;
            if (h == 1ll) { return ans; }
            h = (!h ? K - 1 : h - 1);
            s = fst[pos] + h, tot = fst[pos];
            break;
        } else fst[pos] = tot;
        tot += p[pos].se, pos = p[pos].fi;
    }

    if (s == tot + p[pos].se - 1) { return ans; }

    while (tot <= s) {
        while (tot + p[pos].se <= s) tot += p[pos].se, pos = p[pos].fi;
        if (tot + p[pos].se - 1 == s) break;
        ans.pb(a[pos]), (++pos) %= n, tot++;
    }

    return ans;
}