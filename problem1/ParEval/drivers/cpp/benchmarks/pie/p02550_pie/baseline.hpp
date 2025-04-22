#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll f(ll n, ll m) {
    return (n * n) % m;
}

ll baseline(ll N, ll X, ll M) {
    ll A, preA, ans = 0;
    ll loopcnt = 0, cnt = 0, sum_loop = 0, rec_A;
    vector<int> visit(1000000);
    bool dub = false;

    for(int i = 1; i <= N; i++) {
        if(i == 1) {
            A = X;
            ans += A;
            visit[A] = 1;
            cnt++;
            continue;
        }

        preA = A;
        A = f(A, M);

        if(dub) {
            if(A == rec_A) break;
            ans += A; sum_loop += A; loopcnt++; cnt++;
        } else {
            if(visit[A]) {
                dub = true; rec_A = A; sum_loop += A; loopcnt++;
            }
            ans += A;
            cnt++;
            visit[A] = 1;
        }
    }

    A = preA;

    if(dub) {
        ans += sum_loop * ((N - cnt) / loopcnt);
        ll rem = (N - cnt) % loopcnt;
        for(int i = 0; i < rem; i++) {
            A = f(A, M);
            ans += A;
        }
    }

    return ans;
}

vector<ll> generateInput() {
    ll N = 1e18;
    ll X = 2;
    ll M = 1e9 + 7;
    return {N, X, M};
}