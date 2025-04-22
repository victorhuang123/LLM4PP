#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<string> generateInput(ll N, ll L) {
    vector<string> strings(N);
    for (ll i = 0; i < N; i++) {
        string s(L, 'a' + (i % 26));
        strings[i] = s;
    }
    return strings;
}

ll baseline(ll N, ll L, vector<string>& strings) {
    set<string> ST[100001];
    ll G = 0;
    for (ll i = 0; i < N; i++) {
        string S = strings[i];
        int M = S.size();
        ST[M].insert(S);
    }
    for (int i = 100000; i > 0; i--) {
        if (ST[i].size() & 1) {
            ll K = L - i + 1;
            ll GK = 1;
            while (K % 2 == 0) {
                GK <<= 1;
                K /= 2;
            }
            G ^= GK;
        }
        for (string S : ST[i]) {
            S.pop_back();
            ST[i - 1].insert(S);
        }
        ST[i].clear();
    }
    return G;
}