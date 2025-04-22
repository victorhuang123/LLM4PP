#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> baseline(int N, int A, int B) {
    ll saidai = (ll)A * B;
    int saishou = A + B - 1;
    if (N < saishou || N > saidai) {
        return {-1};
    }

    int amari = N - B;
    vector<int> K;
    for (int i = 0; i < B; i++) {
        int kari = min(A - 1, amari);
        K.push_back(kari);
        amari -= kari;
    }

    vector<int> result;
    for (int i = 0; i < B; i++) {
        for (int j = 0; j <= K[i]; j++) {
            result.push_back(N - K[i] + j);
        }
        N -= K[i] + 1;
    }
    return result;
}

vector<int> generateInput() {
    int N = 1e6;
    int A = 1e3;
    int B = 1e3;
    return {N, A, B};
}