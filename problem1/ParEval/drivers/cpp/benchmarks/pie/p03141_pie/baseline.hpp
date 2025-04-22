#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

ll baseline(int N, vector<pair<int, int>>& input) {
    vector<int> A(N);
    ll goukei = 0;
    rep(i, N) {
        int a = input[i].first;
        int b = input[i].second;
        A[i] = a + b;
        goukei += b;
    }

    sort(A.begin(), A.end(), greater<int>());

    ll kotae = -goukei;
    rep(i, N) if (i % 2 == 0) {
        kotae += A[i];
    }

    return kotae;
}

vector<pair<int, int>> generateInput(int N) {
    vector<pair<int, int>> input(N, make_pair(1e9, 1e9));
    return input;
}