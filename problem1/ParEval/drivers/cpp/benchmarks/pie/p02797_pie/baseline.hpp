#pragma once

#include<bits/stdc++.h>
using namespace std;

vector<int> generate_input(int &N, int &K, int &S) {
    N = 1e6;
    K = 5e5;
    S = 1e9;
    return {N, K, S};
}

vector<int> baseline(int N, int K, int S) {
    vector<int> result(N);
    if (S > N) {
        for (int i = 0; i < K; i++) result[i] = S;
        for (int i = K; i < N; i++) result[i] = 1;
    } else {
        for (int i = 0; i < K; i++) result[i] = S;
        for (int i = K; i < N; i++) result[i] = S + 1;
    }
    return result;
}