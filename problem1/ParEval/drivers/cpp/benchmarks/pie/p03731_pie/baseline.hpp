#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

ll baseline(int N, int T, vector<int>& t) {
    ll kotae = T;
    rep(i, N - 1) {
        kotae += min(T, t[i + 1] - t[i]);
    }
    return kotae;
}

vector<int> generateInput(int N) {
    vector<int> t(N);
    t[0] = 0;
    for (int i = 1; i < N; i++) {
        t[i] = t[i-1] + rand() % 1000000 + 1;
    }
    return t;
}