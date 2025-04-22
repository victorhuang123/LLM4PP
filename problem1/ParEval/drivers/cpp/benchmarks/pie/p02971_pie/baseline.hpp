#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> generate_input(int N) {
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
        A[i] = rand() % 1000000 + 1;
    }
    return A;
}

vector<int> baseline(int N, const vector<int>& A) {
    vector<int> mae(N + 2, 0);
    vector<int> ato(N + 2, 0);

    for (int i = 1; i <= N; i++) {
        mae[i] = max(mae[i - 1], A[i]);
    }

    for (int i = N; i >= 1; i--) {
        ato[i] = max(ato[i + 1], A[i]);
    }

    vector<int> result(N);
    for (int i = 1; i <= N; i++) {
        result[i - 1] = max(mae[i - 1], ato[i + 1]);
    }

    return result;
}