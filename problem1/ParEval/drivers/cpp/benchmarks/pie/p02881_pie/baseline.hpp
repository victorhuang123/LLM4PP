#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> generate_input() {
    return {999999999999999999LL};
}

ll baseline(ll N) {
    int sq = sqrt(N);
    ll saishou = 1e18;
    for (int i = 1; i <= sq; i++) {
        if (N % i == 0) {
            saishou = min(saishou, N / i + i);
        }
    }
    return saishou - 2;
}