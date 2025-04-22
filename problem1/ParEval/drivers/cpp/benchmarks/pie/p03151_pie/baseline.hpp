#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int baseline(int N, vector<int>& A, vector<int>& B) {
    ll tarinai = 0;
    vector<int> V;
    int kotae = 0;

    for (int i = 0; i < N; i++) {
        if (A[i] > B[i]) {
            V.push_back(A[i] - B[i]);
        }
        else if (A[i] < B[i]) {
            tarinai += B[i] - A[i];
            kotae++;
        }
    }
    sort(V.begin(), V.end(), greater<int>());
    for (int i : V) {
        if (tarinai > 0) {
            tarinai -= i;
            kotae++;
        }
        else break;
    }
    if (tarinai > 0) return -1;
    else return kotae;
}

vector<int> generateInput(int N) {
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 1000000 + 1;
        B[i] = rand() % 1000000 + 1;
    }
    return A, B;
}