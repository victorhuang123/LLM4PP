#pragma once

#include <bits/stdc++.h>

using namespace std;

using LL = long long;

#define FOR(i, s, e) for (int(i) = (s); (i) < (e); (i)++)

int baseline(const string& S) {
    int ans = S.size() / 2;
    FOR(i, 0, S.size()) {
        if (S[i] == 'p')
            ans--;
    }
    return ans;
}

string generateInput() {
    const int N = 1e6; // Large input size to test efficiency
    string S(N, 'a');
    for (int i = 0; i < N; i += 2) {
        S[i] = 'p';
    }
    return S;
}