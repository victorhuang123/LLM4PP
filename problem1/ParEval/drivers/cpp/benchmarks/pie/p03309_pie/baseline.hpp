#pragma once

#include <bits/stdc++.h>

using namespace std;

const long long int INF = 1000000000000000000LL;

using ll = long long int;

using vi = vector<int>;

using Vi = vector<long long int>;

#define pb push_back

#define all(x) (x).begin(),(x).end()

#define rep(i,N) for(int i=0;i<N;i++)

auto max(auto x,auto y){if(x>y){return x;}else{return y;}}

template<class T>bool chmax(T &former, const T &b) { if (former<b) { former=b; return 1; } return 0; }

template<class T>bool chmin(T &former, const T &b) { if (b<former) { former=b; return 1; } return 0; }

template<class T>T sqar(T x){ return x*x; }

#define Sort(v) std::sort(v.begin(), v.end(), std::greater<decltype(v[0])>()) //降順でVをソート

ll baseline(ll n, vi& input) {
    vi v;
    ll ar[2*100000+1] = {0};
    long double ma = 0;

    rep(i, n) {
        ar[i] = input[i] - i - 1;
        v.pb(ar[i]);
        ma += (long double)ar[i] / (long double)n;
    }

    sort(all(v));
    ll nya = v[n/2];

    ll ans = 0;
    ll ans2 = 0;
    ll ans3 = 0;
    ll ans4 = 0;

    rep(i, n) {
        ans += abs(ar[i] - (ll)ma);
        ans4 += abs(ar[i] - (ll)nya);
        ans2 += abs(ar[i] - (ll)ma - 1);
        ans3 += abs(ar[i] - (ll)ma + 1);
    }

    return min(ans4, min(ans3, min(ans, ans2)));
}

vi generateInput(ll n) {
    vi input(n);
    rep(i, n) {
        input[i] = rand() % 1000000 + 1;
    }
    return input;
}