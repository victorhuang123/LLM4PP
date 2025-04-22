#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> generateInput(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = (i % 2 == 0) ? -i : i;
    }
    return A;
}

ll baseline(int N, const vector<int>& A) {
    int fu = 0;
    int saishou = 1e9;
    ll goukei = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] < 0) {
            fu++;
            goukei += -A[i];
            saishou = min(saishou, -A[i]);
        } else {
            goukei += A[i];
            saishou = min(saishou, A[i]);
        }
    }

    if (fu % 2) {
        goukei -= saishou * 2;
    }

    return goukei;
}