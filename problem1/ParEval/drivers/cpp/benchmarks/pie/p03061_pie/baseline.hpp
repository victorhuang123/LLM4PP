#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int GCD(int a, int b) { return b ? GCD(b, a % b) : a; }

int baseline(int N, const vector<int>& A) {
    vector<int> l(N + 1, 0), r(N + 1, 0);

    for (int i = 0; i < N; ++i) {
        l[i + 1] = GCD(l[i], A[i]);
    }

    for (int i = N - 1; i >= 0; --i) {
        r[i] = GCD(r[i + 1], A[i]);
    }

    int max_gcd = 0;
    for (int i = 0; i < N; ++i) {
        int ll = l[i], rr = r[i + 1];
        int g = GCD(ll, rr);
        if (max_gcd < g) max_gcd = g;
    }

    return max_gcd;
}

vector<int> generateInput(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = i + 1;
    }
    return A;
}