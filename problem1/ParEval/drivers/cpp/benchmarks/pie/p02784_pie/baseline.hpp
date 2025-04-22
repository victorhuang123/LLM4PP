#pragma once

#include<bits/stdc++.h>
using namespace std;

void generate_input(int& H, int& N, vector<int>& A) {
    H = 1e9;
    N = 1e6;
    A.resize(N);
    for (int i = 0; i < N; i++) {
        A[i] = 1;
    }
}

bool baseline(int H, int N, vector<int>& A) {
    int goukei = 0;
    for (int i = 0; i < N; i++) {
        goukei += A[i];
    }
    return goukei >= H;
}