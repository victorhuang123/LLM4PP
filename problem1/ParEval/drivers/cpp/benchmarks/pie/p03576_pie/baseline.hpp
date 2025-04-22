#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

ll baseline(ll N, ll K, vector<pll>& ps) {
    vector<ll> X(N), Y(N);
    for (int i = 0; i < N; i++) {
        X[i] = ps[i].first;
        Y[i] = ps[i].second;
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());

    ll ans = LLONG_MAX;
    for (int xi = 0; xi < N; xi++) {
        for (int xj = xi + 1; xj < N; xj++) {
            for (int yi = 0; yi < N; yi++) {
                for (int yj = 0; yj < N; yj++) {
                    int cnt = 0;
                    ll minx = X[xi], miny = Y[yi];
                    ll maxx = X[xj], maxy = Y[yj];
                    for (int k = 0; k < N; k++) {
                        if (minx <= ps[k].first &&
                            ps[k].first <= maxx &&
                            miny <= ps[k].second &&
                            ps[k].second <= maxy)
                            cnt++;
                    }
                    if (cnt >= K) {
                        ans = min(ans, (maxx - minx) * (maxy - miny));
                    }
                }
            }
        }
    }

    return ans;
}

vector<pll> generateInput(ll N) {
    vector<pll> ps;
    for (ll i = 1; i <= N; i++) {
        ps.push_back({i, i});
    }
    return ps;
}