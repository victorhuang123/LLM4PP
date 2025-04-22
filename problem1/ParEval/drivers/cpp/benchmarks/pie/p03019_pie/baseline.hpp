#pragma once

#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

typedef long long ll;

bool baseline(ll N, ll X, vector<tuple<ll, ll, ll, ll>>& s, vector<ll>& S, ll Asum, ll canUse) {
    if (canUse >= X * N) return true;

    int r = canUse % X, p = canUse / X;

    for (int i = 0; i < N; i++) {
        ll score = 0;
        score += max(r * get<3>(s[i]) - get<1>(s[i]) * (get<3>(s[i]) - get<2>(s[i])), r * get<2>(s[i]));

        if (score >= Asum && p == 0) return true;

        if (i + 1 <= p) {
            score += S[p + 1] - (X * get<3>(s[i]) - get<1>(s[i]) * (get<3>(s[i]) - get<2>(s[i])));
        } else {
            score += S[p];
        }

        if (score >= Asum) return true;
    }

    return false;
}

vector<tuple<ll, ll, ll, ll>> generateInput(ll N) {
    vector<tuple<ll, ll, ll, ll>> s(N);
    for (ll i = 0; i < N; ++i) {
        s[i] = make_tuple(i, i + 1, i + 2, i + 3);
    }
    return s;
}