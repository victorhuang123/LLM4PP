#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

vll baseline(ll A, ll B, ll Q, vll numsA, vll numsB, vll queries) {
    numsA.push_back(-100000000000LL);
    numsA.push_back(100000000000LL);
    numsB.push_back(-100000000000LL);
    numsB.push_back(100000000000LL);
    sort(numsA.begin(), numsA.end());
    sort(numsB.begin(), numsB.end());

    vll results;
    for (ll x : queries) {
        auto uba = upper_bound(numsA.begin(), numsA.end(), x);
        auto ubb = upper_bound(numsB.begin(), numsB.end(), x);
        auto lba = uba - 1;
        auto lbb = ubb - 1;
        vll tmpA = {*lba, *uba};
        vll tmpB = {*lbb, *ubb};

        ll ans = tmpA[1] - tmpB[0] + min(tmpA[1] - x, x - tmpB[0]);
        ans = min(ans, tmpB[1] - tmpA[0] + min(tmpB[1] - x, x - tmpA[0]));
        ans = min(ans, x - min(tmpA[0], tmpB[0]));
        ans = min(ans, max(tmpA[1], tmpB[1]) - x);

        results.push_back(ans);
    }
    return results;
}

vll generateInput(ll A, ll B, ll Q) {
    vll numsA(A), numsB(B), queries(Q);
    for (ll i = 0; i < A; ++i) numsA[i] = rand() % 1000000000;
    for (ll i = 0; i < B; ++i) numsB[i] = rand() % 1000000000;
    for (ll i = 0; i < Q; ++i) queries[i] = rand() % 1000000000;
    sort(numsA.begin(), numsA.end());
    sort(numsB.begin(), numsB.end());
    return {numsA, numsB, queries};
}