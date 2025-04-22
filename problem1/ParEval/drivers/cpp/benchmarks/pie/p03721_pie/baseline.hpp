#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<int, int>> generateInput(ll N) {
    vector<pair<int, int>> pairs;
    for (int i = 1; i <= N; i++) {
        pairs.push_back({i, i * 10000});
    }
    return pairs;
}

int baseline(ll N, ll K, const vector<pair<int, int>>& pairs) {
    vector<ll> S(100001, 0);
    for (const auto& pair : pairs) {
        S[pair.first] += pair.second;
    }
    int k;
    for (k = 1; k <= 100000; k++) {
        K -= S[k];
        if (K <= 0) break;
    }
    return k;
}