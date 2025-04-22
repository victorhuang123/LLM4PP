#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<int, int>> generateInput(int N, int M) {
    vector<pair<int, int>> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = {rand() % 1000000, rand() % 1000000};
    }
    return A;
}

ll baseline(int N, int M, vector<pair<int, int>> A) {
    sort(A.begin(), A.end());

    int ima = 0;
    ll kotae = 0;
    for (int i = 0; i < N; i++) {
        if (ima < M) {
            int kari = min(M - ima, A[i].second);
            ima += kari;
            kotae += (ll)kari * A[i].first;
        }
    }

    return kotae;
}