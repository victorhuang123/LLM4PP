#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<pair<ll, ll>> generate_input() {
    int M = 1e6;
    vector<pair<ll, ll>> data(M);
    for (int i = 0; i < M; i++) {
        data[i] = {9, 1};
    }
    return data;
}

ll baseline(int M, vector<pair<ll, ll>>& data) {
    ll nagasa = 0;
    ll ketawa = 0;
    for (int i = 0; i < M; i++) {
        ll d = data[i].first;
        ll c = data[i].second;
        ketawa += d * c;
        nagasa += c;
    }

    ll kotae = nagasa - 1;
    kotae += (ketawa - 1) / 9;

    return kotae;
}