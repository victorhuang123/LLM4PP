#pragma once

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

ll baseline(ll n, vector<pair<ll, ll>>& pairs) {
    vector<ll> v;
    for (auto& p : pairs) {
        v.push_back(p.first);
        v.push_back(p.second);
    }
    sort(v.begin(), v.end());

    multiset<ll> one, zero;
    for (ll i = 0; i < n; i++) {
        one.insert(v[i]);
    }
    for (ll i = n; i < 2 * n; i++) {
        zero.insert(v[i]);
    }

    vector<bool> A(n + 1, false), B(n + 1, false);
    multiset<ll> tmp = one;
    ll cnt0 = 0, cnt1 = 0;

    for (ll i = 1; i <= n; i++) {
        if (tmp.count(pairs[i-1].first)) {
            A[i] = true;
            tmp.erase(tmp.find(pairs[i-1].first));
        }
        if (tmp.count(pairs[i-1].second)) {
            B[i] = true;
            tmp.erase(tmp.find(pairs[i-1].second));
        }
        if (!A[i] && !B[i]) {
            cnt0++;
        }
        if (A[i] && B[i]) {
            cnt1++;
        }
    }

    ll ans = 0;
    for (auto it = one.begin(); it != one.end(); it++) {
        ans += *it;
    }

    if (cnt0 || cnt1) {
        return ans;
    }

    set<ll> final;
    for (ll i = 1; i <= n; i++) {
        final.insert(A[i] ? 1 : 0);
    }

    if (final.size() == 1) {
        return ans;
    }

    ll res = 1e18;
    for (ll i = 1; i <= n; i++) {
        if (A[i]) {
            auto it = zero.begin();
            if (pairs[i-1].second == *it) {
                it++;
            }
            res = min(res, ans + (*it - pairs[i-1].first));
        } else {
            auto it = zero.begin();
            if (pairs[i-1].first == *it) {
                it++;
            }
            res = min(res, ans + (*it - pairs[i-1].second));
        }
    }

    return res;
}

vector<pair<ll, ll>> generateInput(ll n) {
    vector<pair<ll, ll>> pairs;
    for (ll i = 0; i < n; i++) {
        pairs.push_back({i + 1, n + i + 1});
    }
    return pairs;
}