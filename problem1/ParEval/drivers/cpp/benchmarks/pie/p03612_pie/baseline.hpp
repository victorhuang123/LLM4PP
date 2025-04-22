#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

int baseline(int N, const vector<int>& p) {
    vector<int> P(N + 1, 0);
    rep1(i, N) {
        P[p[i-1]] = i;
    }
    int kotae = 0;
    rep1(i, N) {
        if (P[i] == i) {
            kotae++;
            i++;
        }
    }
    return kotae;
}

vector<int> generateInput(int N) {
    vector<int> p(N);
    rep(i, N) {
        p[i] = i + 1;
    }
    random_shuffle(p.begin(), p.end());
    return p;
}