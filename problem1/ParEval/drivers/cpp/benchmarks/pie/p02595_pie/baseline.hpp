#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int baseline(ll N, ll D, vector<pair<ll, ll>>& points) {
    int kotae = 0;
    ll D2 = D * D;
    for (int i = 0; i < N; i++) {
        ll X = points[i].first;
        ll Y = points[i].second;
        if (D2 >= X * X + Y * Y) {
            kotae++;
        }
    }
    return kotae;
}

vector<pair<ll, ll>> generate_input(ll N, ll D) {
    vector<pair<ll, ll>> points;
    for (ll i = 0; i < N; i++) {
        ll x = rand() % (2 * D) - D;
        ll y = rand() % (2 * D) - D;
        points.push_back({x, y});
    }
    return points;
}