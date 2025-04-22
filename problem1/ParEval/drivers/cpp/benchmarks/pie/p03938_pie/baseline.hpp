#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

vector<int> baseline(int N, vector<int>& p) {
    vector<int> a(N + 1), b(N + 1);
    rep1(i, N) {
        a[i] = i * 30000;
        b[i] = (N - i + 1) * 30000;
    }
    rep(i, N) {
        a[p[i]] += i;
    }

    vector<int> result;
    rep1(i, N) result.push_back(a[i]);
    rep1(i, N) result.push_back(b[i]);

    return result;
}

vector<int> generateInput(int N) {
    vector<int> p(N);
    rep(i, N) p[i] = i + 1;
    random_shuffle(p.begin(), p.end());
    return p;
}