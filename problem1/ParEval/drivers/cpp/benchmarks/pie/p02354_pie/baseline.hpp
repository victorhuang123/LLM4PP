#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

long long baseline(long long N, long long s, const vector<long long>& a) {
    long long A = LLONG_MAX, l = 0, r = 0;
    vector<long long> S(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        S[i] = S[i - 1] + a[i - 1];
    }

    for (;;) {
        if (S[r] - S[l] >= s) {
            A = min(A, r - l);
            l++;
        } else {
            r++;
        }

        if (r > N || l > N) {
            if (A == LLONG_MAX) A = 0;
            return A;
        }
    }
}

vector<long long> generateInput(long long N) {
    vector<long long> a(N);
    for (long long i = 0; i < N; i++) {
        a[i] = i + 1;
    }
    return a;
}