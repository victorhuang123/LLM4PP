#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll baseline(ll N, ll X, ll D) {
    if (D == 0) {
        if (X == 0) return 1;
        else return N + 1;
    }

    if (D < 0) {
        D *= -1;
        X *= -1;
    }

    ll R = (X ? D / __gcd(abs(X), D) : 1);
    ll Z = (X ? X / __gcd(abs(X), D) : 0);
    int r = 0;
    ll zure = 0;
    ll a = 0;
    ll b = 0;
    ll kotae = 0;
    vector<ll> maeA(min(N + 1, R)), maeB(min(N + 1, R));

    for (int i = 0; i < min(N + 1, R); i++) {
        maeA[i] = a + zure;
        maeB[i] = b + zure;
        kotae += maeB[i] - maeA[i] + 1;
        a += i;
        b += N - i - 1;
        r++;
    }
    r = 0;
    zure += Z;
    for (int i = min(N + 1, R); i <= N; i++) {
        ll A = a + zure;
        ll B = b + zure;
        if (maeA[r] >= A && maeB[r] <= B) {
            kotae += B + maeA[r] - A - maeB[r];
        }
        else if (maeA[r] <= A && maeB[r] >= B) {
            break;
        }
        else if (maeA[r] <= A) {
            kotae += B - max(maeB[r] + 1, A) + 1;
        }
        else {
            kotae += min(maeA[r] - 1, B) - A + 1;
        }
        maeA[r] = A;
        maeB[r] = B;

        a += i;
        b += N - i - 1;
        r++;
        if (r >= R) {
            r = 0;
            zure += Z;
        }
    }
    return kotae;
}

vector<ll> generate_input() {
    ll N = 200000;
    ll X = 1000000000;
    ll D = 1000000000;
    return {N, X, D};
}