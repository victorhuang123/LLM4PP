#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> generateInput(int N) {
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 1000000 + 1;
    }
    return A;
}

ll baseline(int N, const vector<int>& A) {
    vector<ll> B(N + 1), C(N + 1);
    B[0] = 0;
    C[N] = 0;

    vector<int> V;
    ll mae = A[0];
    V.push_back(0);
    for (int i = 0; i < N; i++) {
        ll a = A[i];
        B[i + 1] = B[i];
        if (mae >= a) {
            a *= 4;
            while (mae >= a) {
                V.push_back(0);
                a *= 4;
            }
            V[V.size() - 1]++;
        } else {
            while (mae < a) {
                int kari = V[V.size() - 1];
                B[i + 1] += kari;
                if (V.size() > 1) {
                    V.pop_back();
                    V[V.size() - 1] += kari;
                }
                mae *= 4;
            }
            V[V.size() - 1]++;
        }
        mae = A[i];
    }
    V.clear();
    mae = A[N - 1];
    V.push_back(0);
    for (int i = N - 1; i >= 0; i--) {
        ll a = A[i];
        C[i] = C[i + 1];
        if (mae >= a) {
            a *= 4;
            while (mae >= a) {
                V.push_back(0);
                a *= 4;
            }
            V[V.size() - 1]++;
        } else {
            while (mae < a) {
                int kari = V[V.size() - 1];
                C[i] += kari;
                if (V.size() > 1) {
                    V.pop_back();
                    V[V.size() - 1] += kari;
                }
                mae *= 4;
            }
            V[V.size() - 1]++;
        }
        mae = A[i];
    }

    ll kotae = 1e18;
    for (int i = 0; i <= N; i++) {
        kotae = min(kotae, 2 * B[i] + 2 * C[i] + i);
    }
    return kotae;
}