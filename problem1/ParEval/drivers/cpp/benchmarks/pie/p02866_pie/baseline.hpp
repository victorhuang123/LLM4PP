#pragma once

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 998244353;

ll baseline(const vector<int>& D) {
    int N = D.size();
    if (D[0] != 0) {
        return 0;
    }

    vector<int> sorted_D = D;
    sort(sorted_D.begin(), sorted_D.end());
    int saidai = sorted_D[N - 1];
    vector<int> kazu(200001, 0);
    for (int i = 0; i < N; i++) kazu[sorted_D[i]]++;

    ll kotae = 1;

    if (kazu[0] != 1) {
        return 0;
    }
    if (saidai > N - 1) {
        return 0;
    }

    int mae = 1;
    for (int i = 1; i <= saidai; i++) {
        if (kazu[i] == 0) kotae = 0;
        for (int j = 0; j < kazu[i]; j++) kotae = kotae * mae % mod;
        mae = kazu[i];
    }

    return kotae;
}

vector<int> generate_input() {
    int N = 200000;
    vector<int> D(N);
    D[0] = 0;
    for (int i = 1; i < N; i++) {
        D[i] = rand() % N;
    }
    return D;
}